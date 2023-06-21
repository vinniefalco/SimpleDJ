/*
  ==============================================================================

  Copyright (c) 2012 by Vinnie Falco

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#include "StandardIncludes.h"
#include "Deck.h"
#include "ParamImp.h"
#include "PeakDetector.h"

Deck::Deck (vf::CallQueue& mixerThread, Params& params)
  : Mixer::Source (mixerThread)
  , param (params)
{
}

class DeckImp : public Deck
{
private:
  /** Shared state information.
  */
  struct State
  {
    State ()
    {
      levels.left.peak = 0;
      levels.left.clip = false;
      levels.right.peak = 0;
      levels.right.clip = false;
    }

    Levels levels;
    Playable::Ptr playable;
  };

  typedef vf::ConcurrentState <State> StateType;

  StateType m_state;
  vf::Listeners <Listener> m_listeners;
  bool m_isPreparedToPlay;
  int m_samplesPerBlockExpected;
  double m_sampleRate;
  ScopedPointer <ResamplingAudioSource> m_resampler;
  ScopedPointer <PeakDetector <2, float> > m_peakDetector;

  bool m_isPlaying;
  float m_deckVolume;

  Params m_params;
  ScopedPointer <ParamImp> m_paramVol;
  ScopedPointer <ParamImp> m_paramPlay;
  ScopedPointer <ParamImp> m_paramSpeed;

public:
  explicit DeckImp (vf::CallQueue& mixerThread)
    : Deck (mixerThread, m_params)
    , m_isPreparedToPlay (false)
    , m_samplesPerBlockExpected (0)
    , m_sampleRate (0)
    , m_peakDetector (new PeakDetector <2, float>)
    , m_isPlaying (false)
    , m_deckVolume (1)
    , m_paramVol (new ParamImp ("vol", m_deckVolume, mixerThread, &m_params))
    , m_paramPlay (new ParamImp ("play", 0, mixerThread, &m_params))
    , m_paramSpeed (new ParamImp ("speed", 0, mixerThread, &m_params))
  {
  }

  ~DeckImp()
  {
  }

  /** Create a new resampler to wrap the Playable, or clear the old one.
  */
  void prepareToPlayResampler ()
  {
    StateType::UnlockedAccess state (m_state);

    if (state->playable != nullptr && m_isPreparedToPlay)
    {
      m_resampler = new ResamplingAudioSource (state->playable, false, 2);

      m_resampler->prepareToPlay (m_samplesPerBlockExpected, m_sampleRate);
    }
    else
    {
      m_resampler = nullptr;
    }
  }

  /** This is called on the mixer thread.
  */
  void doSelectPlayable (Playable::Ptr playable)
  {
    if (StateType::UnlockedAccess (m_state)->playable != playable)
    {
      // Turn off playback
      if (m_isPlaying)
      {
        m_isPlaying = false;

        m_paramPlay->setValue (0);
      }

      {
        // Atomically change the Playable.

        StateType::WriteAccess state (m_state);

        state->playable = playable;

        m_listeners.queue (&Listener::onDeckSelect, this, playable);
      }

      prepareToPlayResampler ();
    }
  }

  //============================================================================
  //
  // Deck
  //

  void addListener (Listener* listener, vf::CallQueue& thread)
  {
    // Atomically add the listener and synchronize their state.

    StateType::ReadAccess state (m_state);

    m_listeners.add (listener, thread);

    m_listeners.queue1 (listener, &Listener::onDeckLevels, this, state->levels);

    m_listeners.queue1 (listener, &Listener::onDeckSelect, this, state->playable);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void selectPlayable (Playable::Ptr playable)
  {
    getThread().call (&DeckImp::doSelectPlayable, this, playable);
  }

  //============================================================================
  //
  // AudioSource
  //

  void prepareToPlay (int samplesPerBlockExpected, double sampleRate)
  {
    jassert (!m_isPreparedToPlay);

    m_isPreparedToPlay = true;

    m_samplesPerBlockExpected = samplesPerBlockExpected;
    m_sampleRate = sampleRate;

    prepareToPlayResampler ();

    m_peakDetector->setup (sampleRate);
  }

  void releaseResources()
  {
    jassert (m_isPreparedToPlay);

    m_isPreparedToPlay = false;

    m_resampler = nullptr;
  }

  void produceOutput (AudioSampleBuffer& outputBuffer)
  {
  }

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
  {
    // Detect play state change.
    {
      bool const wantsPlaying = m_paramPlay->getValue () != 0;

      if (m_isPlaying != wantsPlaying)
      {
        if (wantsPlaying)
        {
          if (m_isPreparedToPlay && m_resampler != nullptr)
          {
            // Turn it on.
            m_isPlaying = true;
          }
          else
          {
            // Tried to set play with no device or no Playable.
            m_paramPlay->setValue (0);
          }
        }
        else
        {
          // Turn it off.
          m_isPlaying = false;
        }
      }
    }

    if (m_isPlaying)
    {
      jassert (m_isPreparedToPlay && m_resampler != nullptr);

      StateType::UnlockedAccess state (m_state);

      double const speed = pow (2., m_paramSpeed->getValue ());

      m_resampler->setResamplingRatio (speed * state->playable->getSampleRate () / m_sampleRate);

      m_resampler->getNextAudioBlock (bufferToFill);
    }
    else
    {
      // Output silence
      bufferToFill.clearActiveBufferRegion ();
    }

    // Calculate levels (pre deck fader)
    Levels newLevels;

    m_peakDetector->process (bufferToFill.numSamples,
      bufferToFill.buffer->getArrayOfWritePointers());

    newLevels.left.peak = (*m_peakDetector)[0];
    newLevels.left.clip = false;

    newLevels.right.peak = (*m_peakDetector)[1];
    newLevels.right.clip = false;

    // Apply deck fader.
    bufferToFill.buffer->applyGainRamp (0, 0, bufferToFill.numSamples,
      m_deckVolume, m_paramVol->getValue ());
    bufferToFill.buffer->applyGainRamp (1, 0, bufferToFill.numSamples,
      m_deckVolume, m_paramVol->getValue ());
    m_deckVolume = m_paramVol->getValue ();

    // Update shared state.
    {
      StateType::WriteAccess state (m_state);

      state->levels = newLevels;
    }

    // Notify listeners.
    m_listeners.update (&Listener::onDeckLevels, this, newLevels);
  }
};

Deck::Ptr Deck::New (vf::CallQueue& mixerThread)
{
  return new DeckImp (mixerThread);
}

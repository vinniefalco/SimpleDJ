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

Deck::Deck (vf::CallQueue& mixerThread)
  : Mixer::Source (mixerThread)
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

      isPlaying = false;
    }

    bool isPlaying;
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

public:
  explicit DeckImp (vf::CallQueue& mixerThread)
    : Deck (mixerThread)
    , m_isPreparedToPlay (false)
    , m_samplesPerBlockExpected (0)
    , m_sampleRate (0)
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

      m_resampler->setResamplingRatio (state->playable->getSampleRate () / m_sampleRate);

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
      {
        // Atomically turn off playback and change the Playable.
  
        StateType::WriteAccess state (m_state);

        if (state->isPlaying)
        {
          state->isPlaying = false;

          m_listeners.queue (&Listener::onDeckPlay, this, false);
        }

        state->playable = playable;

        m_listeners.queue (&Listener::onDeckSelect, this, playable);
      }

      {
        // Prepare the Playable if necessary.

        StateType::UnlockedAccess state (m_state);

        if (state->playable != nullptr && m_isPreparedToPlay)

          state->playable->prepareToPlay (m_samplesPerBlockExpected,
                                          m_sampleRate);
      }

      prepareToPlayResampler ();
    }
  }

  /** Change the play state.

      This is called on the mixer thread.
  */
  void doSetPlay (bool shouldBePlaying)
  {
    StateType::UnlockedAccess state (m_state);

    // Change play state only if its different, and only
    // allow turning play on if there's a Playable selected.
    if (state->isPlaying != shouldBePlaying &&
        ( !shouldBePlaying || state->playable != nullptr) )
    {
      // Atomically change the play state

      StateType::WriteAccess state (m_state);

      state->isPlaying = shouldBePlaying;

      m_listeners.queue (&Listener::onDeckPlay, this, state->isPlaying);
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

    m_listeners.queue1 (listener, &Listener::onDeckPlay, this, state->isPlaying);

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

  void setPlay (bool shouldBePlaying)
  {
    getThread().call (&DeckImp::doSetPlay, this, shouldBePlaying);
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
  }

  void releaseResources()
  {
    jassert (m_isPreparedToPlay);

    m_isPreparedToPlay = false;

    m_resampler = nullptr;
  }

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
  {
    AudioSampleBuffer outputBuffer (*bufferToFill.buffer);

    if (m_resampler != nullptr)
    {
      m_resampler->getNextAudioBlock (bufferToFill);
    }
    else
    {
      // Output silence
      outputBuffer.clear ();
    }

    Levels newLevels;
    newLevels.left.peak = 0;
    newLevels.left.clip = false;
    newLevels.right.peak = 0;
    newLevels.right.clip = false;

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

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
#include "Mixer.h"

class MixerImp
  : public Mixer
  , private AudioIODeviceCallback
{
private:
  /** Shared state information.
  */
  struct State
  {
    State ()
    {
      level.left.peak = 0;
      level.left.clip = false;
      level.right.peak = 0;
      level.right.clip = false;
    }

    StereoLevel level;
  };

  typedef vf::ConcurrentState <State> StateType;

  StateType m_state;
  vf::ManualCallQueue m_thread;
  vf::Listeners <Listener> m_listeners;

  AudioIODevice* m_device;
  ReferenceCountedArray <Source> m_sources;
  ScopedPointer <AudioDeviceManager> m_audioDeviceManager;

public:
  MixerImp ()
    : m_thread ("Mixer")
    , m_device (nullptr)
    , m_audioDeviceManager (new AudioDeviceManager)
  {
    // set up audio device
    {
      int sampleRate = 44100;
      int bufferSize;
      int latencyMilliseconds=50;

      bufferSize = sampleRate * latencyMilliseconds / 1000;

      AudioDeviceManager::AudioDeviceSetup setup;
      m_audioDeviceManager->initialise (0, 2, 0, true);
      m_audioDeviceManager->setCurrentAudioDeviceType ("DirectSound", false);
      m_audioDeviceManager->getAudioDeviceSetup (setup);

      setup.sampleRate = sampleRate;
      setup.bufferSize = bufferSize;
      setup.useDefaultInputChannels = false;
      setup.inputChannels = 0;
      setup.useDefaultOutputChannels = true;
      setup.outputChannels = 2;

      String result = m_audioDeviceManager->setAudioDeviceSetup (setup, false);

      m_audioDeviceManager->addAudioCallback (this);
    }
  }

  ~MixerImp()
  {
    // Flush what's left in the fifo since its manual.
    m_thread.close ();
    m_thread.synchronize ();

    m_audioDeviceManager->closeAudioDevice ();
  }

  //============================================================================
  //
  // MixerImp
  //
  
  /** Add a Source.

      This is called on the mixer thread.
  */
  void doAddSource (Source::Ptr source)
  {
    m_sources.add (source);
  }

  /** Remove a Source.

      This is called on the mixer thread.
  */
  void doRemoveSource (Source::Ptr source)
  {
    m_sources.removeObject (source);
  }

  //============================================================================
  //
  // Mixer
  //

  AudioDeviceManager& getAudioDeviceManager()
  {
    return *m_audioDeviceManager;
  }

  void addListener (Listener* listener, vf::CallQueue& thread)
  {
    /* Atomically add the listener and synchronize their state. */

    StateType::ReadAccess state (m_state);

    m_listeners.add (listener, thread);

    m_listeners.queue1 (listener, &Listener::onMixerOutputLevel, state->level);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void addSource (Source::Ptr source)
  {
    /* Do this on the mixer thread. */
    m_thread.call (&MixerImp::doAddSource, this, source);
  }

  void removeSource (Source::Ptr source)
  {
    /* Do this on the mixer thread. */
    m_thread.call (&MixerImp::doRemoveSource, this, source);
  }

  //============================================================================
  //
  // AudioIODeviceCallback
  //

  void audioDeviceAboutToStart (AudioIODevice* device)
  {
    m_device = device;
  }

  void audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
  {
    /* Synchronize state. */
    m_thread.synchronize ();

    AudioSampleBuffer outputBuffer (outputChannelData, numOutputChannels, numSamples);

    StereoLevel newLevel;
    newLevel.left.peak = 0;
    newLevel.left.clip = false;
    newLevel.right.peak = 0;
    newLevel.right.clip = false;

    /* Update shared state. */
    {
      StateType::WriteAccess state (m_state);

      state->level = newLevel;
    }

    /* Notify listeners. */
    m_listeners.call (&Listener::onMixerOutputLevel, newLevel);
  }

  void audioDeviceStopped ()
  {
  }
};

Mixer* Mixer::New ()
{
  return new MixerImp;
}

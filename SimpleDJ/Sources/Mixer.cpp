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
      levels.left.peak = 0;
      levels.left.clip = false;
      levels.right.peak = 0;
      levels.right.clip = false;
    }

    Levels levels;
  };

  struct SourceData
  {
    SourceData () : buffer (2, 0)
    {
    }

    AudioSampleBuffer buffer;
  };

  typedef vf::ConcurrentState <State> StateType;

  StateType m_state;
  vf::ManualCallQueue m_thread;
  vf::Listeners <Listener> m_listeners;
  AudioIODevice* m_currentDevice;
  ReferenceCountedArray <Source> m_sources;
  Array <SourceData> m_sourceData;
  ScopedPointer <AudioDeviceManager> m_audioDeviceManager;
  AudioSampleBuffer m_sourceBuffer;

public:
  MixerImp ()
    : m_thread ("Mixer")
    , m_currentDevice (nullptr)
    , m_audioDeviceManager (new AudioDeviceManager)
    , m_sourceBuffer (2, 0)
  {
    // set up audio device
    int sampleRate = 96000;
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

    // Prepare the source if we're already open.
    if (m_currentDevice != nullptr)
    {
      int const samplesPerBlockExpected = m_currentDevice->getCurrentBufferSizeSamples ();
      double const sampleRate = m_currentDevice->getCurrentSampleRate ();

      source->prepareToPlay (samplesPerBlockExpected, sampleRate);
    }
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

  vf::CallQueue& getThread ()
  {
    return m_thread;
  }

  void addListener (Listener* listener, vf::CallQueue& thread)
  {
    // Atomically add the listener and synchronize their state.

    StateType::ReadAccess state (m_state);

    m_listeners.add (listener, thread);

    m_listeners.queue1 (listener, &Listener::onMixerLevels, this, state->levels);
  }

  void removeListener (Listener* listener)
  {
    m_listeners.remove (listener);
  }

  void addSource (Source::Ptr source)
  {
    m_thread.call (&MixerImp::doAddSource, this, source);
  }

  void removeSource (Source::Ptr source)
  {
    m_thread.call (&MixerImp::doRemoveSource, this, source);
  }

  //============================================================================
  //
  // AudioIODeviceCallback
  //

  void audioDeviceAboutToStart (AudioIODevice* device)
  {
    jassert (m_currentDevice == nullptr);
    m_currentDevice = device;

    // Prepare each Source.
    for (int i = 0; i < m_sources.size (); ++i)
    {
      Source::Ptr source = m_sources [i];
      int const samplesPerBlockExpected = device->getCurrentBufferSizeSamples ();
      double const sampleRate = device->getCurrentSampleRate ();

      source->prepareToPlay (samplesPerBlockExpected, sampleRate);
    }
  }

  void processSource (int sourceIndex)
  {
    m_sources [sourceIndex]->getNextAudioBlock (
      AudioSourceChannelInfo (m_sourceData.getReference (sourceIndex).buffer));
  }

  void audioDeviceIOCallback (const float** inputChannelData,
                              int numInputChannels,
                              float** outputChannelData,
                              int numOutputChannels,
                              int numSamples)
  {
    // Synchronize state.
    m_thread.synchronize ();

    // Prepare intermediate data
    m_sourceData.resize (m_sources.size ());
    for (int i = 0; i < m_sources.size (); ++i)
      m_sourceData.getReference (i).buffer.setSize (2, numSamples, false, false, true);

    // Process sources in parallel.
    vf::ParallelFor().loop (m_sources.size(), &MixerImp::processSource, this);

    // Set up the output data.
    AudioSampleBuffer outputBuffer (outputChannelData, numOutputChannels, numSamples);

    // Add Sources to output.
    if (m_sources.size () > 0)
    {
      outputBuffer.copyFrom (0, 0, m_sourceData [0].buffer.getArrayOfChannels ()[0], numSamples);
      outputBuffer.copyFrom (1, 0, m_sourceData [0].buffer.getArrayOfChannels ()[1], numSamples);
      for (int i = 1; i < m_sources.size (); ++i)
      {
        outputBuffer.addFrom (0, 0, m_sourceData [i].buffer.getArrayOfChannels ()[0], numSamples);
        outputBuffer.addFrom (1, 0, m_sourceData [i].buffer.getArrayOfChannels ()[1], numSamples);
      }
    }
    else
    {
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
    m_listeners.update (&Listener::onMixerLevels, this, newLevels);
  }

  void audioDeviceStopped ()
  {
    /* A nullptr indicates the device is closed */
    m_currentDevice = nullptr;
  }
};

Mixer* Mixer::New ()
{
  return new MixerImp;
}

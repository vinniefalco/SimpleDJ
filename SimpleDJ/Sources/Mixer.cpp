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

Mixer::Mixer ()
  : m_thread ("Mixer")
  , m_audioDeviceManager (new AudioDeviceManager)
  , m_device (nullptr)
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

Mixer::~Mixer()
{
  // Flush what's left in the fifo since its manual.
  m_thread.close ();
  m_thread.synchronize ();

  m_audioDeviceManager->closeAudioDevice ();
}

AudioDeviceManager& Mixer::getAudioDeviceManager()
{
  return *m_audioDeviceManager;
}

//
// AudioIODeviceCallback
//

void Mixer::audioDeviceAboutToStart (AudioIODevice* device)
{
  m_device = device;
}

void Mixer::audioDeviceIOCallback (const float** inputChannelData,
                                         int numInputChannels,
                                         float** outputChannelData,
                                         int numOutputChannels,
                                         int numSamples)
{
  m_thread.synchronize ();

  AudioSampleBuffer outputBuffer (outputChannelData, numOutputChannels, numSamples);
}

void Mixer::audioDeviceStopped ()
{
}

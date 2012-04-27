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

#ifndef MIXER_HEADER
#define MIXER_HEADER

/** Mixer for audio output.
*/
class Mixer
{
public:
  /** Describes a channel's output level.
  */
  struct Level
  {
    float peak; //! Post-compressor level, range [0,1]
    bool clip;  //! true if channel caused clipping.
  };

  /** Output level for a stereo signal.
  */
  struct StereoLevel
  {
    Level left;   //! left channel level
    Level right;  //! right channel level
  };

  /** Audio provider for Mixer.
  */
  class Source
    : public vf::ConcurrentObject
    , public AudioSource
  {
  public:
    typedef ReferenceCountedObjectPtr <Source> Ptr;

    explicit Source (vf::CallQueue& mixerThread) : m_thread (mixerThread)
    {
    }

  protected:
    vf::CallQueue& getThread ()
    {
      return m_thread;
    }

  private:
    vf::CallQueue& m_thread;
  };

  /** Synchronizes the Mixer state
  */
  class Listener
  {
  public:
    virtual void onMixerOutputLevel (StereoLevel const level) { }
  };

public:
  static Mixer* New ();

  virtual ~Mixer () { }

  /** Get the raw AudioDeviceManager.
  */
  virtual AudioDeviceManager& getAudioDeviceManager() = 0;

  /** Add or remove a Mixer::Listener.
  */
  virtual void addListener (Listener* listener, vf::CallQueue& thread) = 0;
  virtual void removeListener (Listener* listener) = 0;

  /** Add or remove a Source.
  */
  virtual void addSource (Source::Ptr source) = 0;
  virtual void removeSource (Source::Ptr source) = 0;
};

#endif

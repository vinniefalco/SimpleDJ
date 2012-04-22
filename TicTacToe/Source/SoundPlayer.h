/*
==============================================================================
            Sound playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==============================================================================
*/

/** be fit for playback a shorter sound(audio file or inputStream)..

 usage(in context component class): 
 1) declare this class' object
 2) call play(...)

**/
#ifndef __SOUNDPLAYER_H_
#define __SOUNDPLAYER_H_

#include "../JuceLibraryCode/JuceHeader.h"

//============================================================================
class SoundPlayer
{
public:
    //========================================================================
    SoundPlayer();
    ~SoundPlayer();   

    void play(InputStream* inputStream);
    void play(const File& audioFile);

private:
    //========================================================================
    void stop();

    AudioDeviceManager deviceManager;

    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> formatReaderSource;
    AudioTransportSource transportSource;
    AudioSourcePlayer sourcePlayer;

    TimeSliceThread sliceThread;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundPlayer)
};

#endif  // __SOUNDPLAYER_H_

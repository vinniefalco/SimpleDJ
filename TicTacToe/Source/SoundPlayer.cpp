/*
==================================================================================
            Sound playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==================================================================================
*/

#include "SoundPlayer.h"

//=================================================================================

SoundPlayer::SoundPlayer() : sliceThread("SoundPlayback")
{
    deviceManager.initialise( 0, 2, nullptr, true );
    formatManager.registerBasicFormats();

    sliceThread.startThread (3);
    
    sourcePlayer.setSource(&transportSource);
    deviceManager.addAudioCallback(&sourcePlayer);
}
//=================================================================================
SoundPlayer::~SoundPlayer()
{    
    transportSource.setSource(nullptr);
    sourcePlayer.setSource (nullptr);
    deviceManager.removeAudioCallback(&sourcePlayer);
}
//=================================================================================
void SoundPlayer::play(InputStream* inputStream)
{
    stop(); 

    AudioFormatReader* reader = formatManager.createReaderFor (inputStream);

    if (reader != nullptr)
    {
        formatReaderSource = new AudioFormatReaderSource(reader, true);
        transportSource.setSource
            (formatReaderSource, 32768, &sliceThread, reader->sampleRate);
        transportSource.start();
    }
}
//==================================================================================
void SoundPlayer::play(const File& audioFile)
{
    stop();

    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);  

    if (reader != nullptr)
    {
        formatReaderSource = new AudioFormatReaderSource(reader, true);
        transportSource.setSource
            (formatReaderSource, 32768, &sliceThread, reader->sampleRate);
        transportSource.start();
    }
}
//==================================================================================
void SoundPlayer::stop()
{
    transportSource.stop();
    transportSource.setSource (nullptr);
    formatReaderSource = nullptr; 
}


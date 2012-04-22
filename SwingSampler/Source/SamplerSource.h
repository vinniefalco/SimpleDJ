/*
================================================================================
            S-Sampler

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// sampler audio source.

#ifndef __SAMPLERSOURCE_H_
#define __SAMPLERSOURCE_H_

class BaseComp;
//===============================================================================
class SamplerSource : public AudioSource
{
public:  
    //===========================================================================
    enum SoundSource {SINEWAVE = 0x0001, PIANO, VIOLA, TAIKO};

    SamplerSource (MidiKeyboardState& State, BaseComp* base);    

    void prepareToPlay (int /*samplesPerBlock*/, double sampleRate);    
    void getNextAudioBlock (const AudioSourceChannelInfo& buffers);
    void releaseResources() {}
    
    void setSampledSound(SoundSource whichSound = SINEWAVE);
    void setSampledSound(const File& audioFile);
    void loadSound(int rootNote);

    MidiMessageCollector midiCollector;

private:
    //===========================================================================
    BaseComp* baseComp;

    MidiKeyboardState& keyboardState;
    Synthesiser synth;

    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReader> reader;
};

#endif  // __SAMPLERSOURCE_H_
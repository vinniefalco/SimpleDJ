/*
================================================================================
            S-Sampler

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// sine wave audio source.

#ifndef __SINEWAVEVOICE_H_
#define __SINEWAVEVOICE_H_

//===================================================================================
class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound()    { }
    bool appliesToNote (const int /*midiNoteNumber*/)   { return true; }
    bool appliesToChannel (const int /*midiChannel*/)   { return true; }
};

//==================================================================================
class SineWaveVoice : public SynthesiserVoice 
{
public:
    SineWaveVoice();
    bool canPlaySound (SynthesiserSound* sound);
    void startNote (const int midiNoteNumber, const float velocity, 
        SynthesiserSound* , const int);
    void stopNote (const bool allowTailOff);
    void pitchWheelMoved (const int /*newValue*/)  { }
    void controllerMoved (const int /*controllerNumber*/, const int /*newValue*/) { }
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples);

private:
    double currentAngle, angleDelta, level, tailOff;
};

#endif // __SINEWAVEVOICE_H_
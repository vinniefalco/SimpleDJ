/*
====================================================================================
S-Sampler

Author: SwingCoder
Email: SwingCoder2@gmail.com
Github: https://github.com/SwingCoder

License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SineWaveVoice.h"

//====================================================================================

SineWaveVoice::SineWaveVoice() : angleDelta (0.0), tailOff (0.0) 
{
}    
//====================================================================================
bool SineWaveVoice::canPlaySound (SynthesiserSound* sound) 
{
    return dynamic_cast <SineWaveSound*> (sound) != nullptr;
}
//====================================================================================
void SineWaveVoice::startNote (const int midiNoteNumber, const float velocity, 
    SynthesiserSound* , const int) 
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    double cyclesPerSample = cyclesPerSecond / getSampleRate();
    angleDelta = cyclesPerSample * 2.0 * double_Pi;
}
//====================================================================================
void SineWaveVoice::stopNote (const bool allowTailOff) 
{
    if (allowTailOff) 
    {
        if (tailOff == 0.0) 
            tailOff = 1.0;
    } 
    else 
    {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}
//====================================================================================
void SineWaveVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, 
    int startSample, int numSamples)
{
    if (angleDelta != 0.0) 
    {
        if (tailOff > 0) 
        {
            while (--numSamples >= 0) 
            {
                const float currentSample = (float) (sin (currentAngle) * level * tailOff);
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    *outputBuffer.getSampleData (i, startSample) += currentSample;

                currentAngle += angleDelta;
                ++startSample;
                tailOff *= 0.99;

                if (tailOff <= 0.005)  
                {
                    clearCurrentNote();
                    angleDelta = 0.0;
                    break;
                }
            }
        }   
        else  
        {
            while (--numSamples >= 0) 
            {
                const float currentSample = (float) (sin (currentAngle) * level);

                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    *outputBuffer.getSampleData (i, startSample) += currentSample;

                currentAngle += angleDelta;
                ++startSample;
            }
        }
    }
}

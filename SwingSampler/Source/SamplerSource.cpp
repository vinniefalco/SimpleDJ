/*
=======================================================================================
            S-Sampler

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
=======================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComp.h"
#include "SamplerSource.h"
#include "SineWaveVoice.h"

//======================================================================================
SamplerSource::SamplerSource (MidiKeyboardState& state, BaseComp* base) : 
        keyboardState (state),
        baseComp(base),
        reader(nullptr)
{
    formatManager.registerBasicFormats();

    for (int i = 0; i < 2; ++i)
    {
        synth.addVoice (new SineWaveVoice());
        synth.addVoice (new SamplerVoice()); 
    }
}
//=======================================================================================
void SamplerSource::prepareToPlay (int /*samplesPerBlock*/, double sampleRate) 
{
    midiCollector.reset (sampleRate);
    synth.setCurrentPlaybackSampleRate (sampleRate);
}
//========================================================================================
void SamplerSource::getNextAudioBlock (const AudioSourceChannelInfo& buffers) 
{
    buffers.clearActiveBufferRegion();

    MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages (incomingMidi, buffers.numSamples);
    keyboardState.processNextMidiBuffer (incomingMidi, 0, buffers.numSamples, true);

    synth.renderNextBlock (*buffers.buffer, incomingMidi, 0, buffers.numSamples);
}
//=======================================================================================
void SamplerSource::setSampledSound(SoundSource whichSound)    
{
    MemoryInputStream* inputStream = nullptr;
    
    switch (whichSound)   // set inputStream (tone)..
    {
    case SINEWAVE:
        synth.clearSounds();
        synth.addSound(new SineWaveSound());
        baseComp->rootSetCb->setEnabled(false);
        return;

    case PIANO:
        inputStream= new MemoryInputStream
            (BinaryData::piano_mp3, BinaryData::piano_mp3Size, false);
        break;

    case VIOLA:
        inputStream= new MemoryInputStream
            (BinaryData::violin_mp3, BinaryData::violin_mp3Size, false);
        break;

    case TAIKO:
        inputStream= new MemoryInputStream
            (BinaryData::taiko_mp3, BinaryData::taiko_mp3Size, false);
        break;

    default:
        inputStream= new MemoryInputStream
            (BinaryData::piano_mp3, BinaryData::piano_mp3Size, false);
        break;
    }
        
    reader = formatManager.createReaderFor (inputStream);

    baseComp->rootSetCb->setEnabled(true);
    baseComp->rootSetCb->setSelectedId(10);

    loadSound(72);  
}
//=======================================================================================
void SamplerSource::setSampledSound(const File& audioFile)
{
    reader = formatManager.createReaderFor (audioFile);

    if (reader != nullptr)
    {
        baseComp->toneSetCb->setEnabled(false);
        baseComp->fileInfoLb->setText(audioFile.getFullPathName(), false);
        baseComp->rootSetCb->setSelectedId(10);

        loadSound(72);  

        baseComp->rootSetCb->setEnabled(true);
    }
    else
    {
        AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
            TRANS("Sorry"), 
            TRANS("I can't digest this food..."));

        baseComp->toneSetCb->setEnabled(true);
        baseComp->toneSetCb->setSelectedId(1);
        baseComp->rootSetCb->setSelectedId(10);
        baseComp->fileInfoLb->setText(String::empty, false);

        setSampledSound(SINEWAVE);
        baseComp->rootSetCb->setEnabled(false);
    }
}
//=======================================================================================
void SamplerSource::loadSound(int rootNote)
{
    if (reader != nullptr)
    {
        synth.clearSounds();  

        BigInteger notes;
        notes.setRange (0, 128, true);

        SamplerSound* tone = new SamplerSound ("tone", *reader, notes, rootNote, 0.0, 0.1, 60.0);
        synth.addSound (tone);
    }
    else
    {
        synth.clearSounds();
        synth.addSound(new SineWaveSound());
    }
}
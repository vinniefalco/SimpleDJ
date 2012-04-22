/*
================================================================================
            MIDI Playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiPlayer.h"

//===============================================================================

MidiPlayer::MidiPlayer () : midiOutput(MidiOutput::openDevice(0))
{ 
}
//=================================================================================
MidiPlayer::~MidiPlayer()
{
}
//=================================================================================
void MidiPlayer::selectMidiDevice()
{
    // get all midi output deveices and add them to menu.
    StringArray midiDevices = MidiOutput::getDevices();
    PopupMenu menu;

    for (int i = 0; i < midiDevices.size(); ++i)
    {
        menu.addItem(i + 1, midiDevices[i], true, midiOutput->getDefaultDeviceIndex() == i);        
    }

    // set midi output device to used.
    midiOutput = MidiOutput::openDevice(menu.show());
}
//=================================================================================
void MidiPlayer::playMidi()
{
    if (midiOutput != nullptr)
    {
        MidiFile midiFile;
        const MidiMessageSequence* midiMessageSeque;
        MidiMessage message;
        MidiBuffer buffer;

        // get midi file..        
        FileInputStream fileStream(File("E://00.mid")); 
        midiFile.readFrom(fileStream);  
        midiFile.convertTimestampTicksToSeconds();

        midiOutput->startBackgroundThread();

        for (int i = 0; i < midiFile.getNumTracks(); ++i)
        {
            midiMessageSeque = midiFile.getTrack(i);

            for (int i = 0; i < midiMessageSeque->getNumEvents(); ++i)
            {
                message = midiMessageSeque->getEventPointer(i)->message;
                buffer.addEvent(message, midiMessageSeque->getNumEvents());
            }  
        }
        
        midiOutput->sendBlockOfMessages(buffer, 2000.0, 22050.0);

        buffer.clear();
    }
}
//=================================================================================
void MidiPlayer::stopMidi()
{
    if (midiOutput != nullptr)
    {
        midiOutput->clearAllPendingMessages();
        midiOutput->stopBackgroundThread();
    }
}
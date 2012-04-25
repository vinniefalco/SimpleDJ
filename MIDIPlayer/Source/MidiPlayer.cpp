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

void MidiPlayer::playMidi(File& file)
{
  if (midiOutput != nullptr)
  {
     // get MidiFile..
    FileInputStream fileStream (file); 
    MidiFile midiFile;
    midiFile.readFrom (fileStream);  

    // midi file convert to MidiBuffer
    MidiBuffer buffer;

    // Loop over all tracks
    for (int trackIndex = 0; trackIndex < midiFile.getNumTracks (); ++trackIndex)
    {
      const MidiMessageSequence* messageSequence = midiFile.getTrack (trackIndex);

      // Loop over all events of current track.
      for (int i = 0; i < messageSequence->getNumEvents (); ++i)
      {
        // Add the message, preserving the time stamp
        MidiMessage message = messageSequence->getEventPointer (i)->message;
        buffer.addEvent (message, int(message.getTimeStamp ()));
      }
    }
    // Start the background thread right away
    midiOutput->startBackgroundThread();
    // Now send the entire block of messages, have it start 0.1 seconds from now.
    midiOutput->sendBlockOfMessages(buffer, Time::getMillisecondCounter() + 50, 1000);
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
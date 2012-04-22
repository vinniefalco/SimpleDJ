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
    // Start the background thread right away
    midiOutput->startBackgroundThread();

    // Open up our file
    FileInputStream fileStream (File ("E://00.mid")); 

    // Now read the MIDI data
    MidiFile midiFile;
    midiFile.readFrom (fileStream);  

    // We will convert the entire file into one MidiBuffer
    MidiBuffer b;

    // Loop over all tracks
    for (int trackIndex = 0; trackIndex < midiFile.getNumTracks (); ++trackIndex)
    {
      MidiMessageSequence const* track = midiFile.getTrack (trackIndex);

      // Loop over all events
      for (int index = 0; index < track->getNumEvents (); ++index)
      {
        // Add the message, preserving the time stamp

        MidiMessage m = track->getEventPointer (index)->message;
        b.addEvent (m, m.getTimeStamp ());

        // For debugging
        //Logger::outputDebugString (String (m.getTimeStamp ()));
      }
    }

    // Now send the entire block of messages, have it start 0.1 seconds from now.
    midiOutput->sendBlockOfMessages(b, Time::getMillisecondCounter() + 100, 1000);
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
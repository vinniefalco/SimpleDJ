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

    // samples per second. sendBlockOfMessages() will use this double value.
    // 960 ticks and 120BPM..
    double samples = 1920;

    // Loop over all tracks
    for (int trackIndex = 0; trackIndex < midiFile.getNumTracks (); ++trackIndex)
    {
      const MidiMessageSequence* messageSequence = midiFile.getTrack (trackIndex);

      // Loop over all events of current track.
      for (int i = 0; i < messageSequence->getNumEvents (); ++i)
      {
        // Add every message to buffer..
        MidiMessage message = messageSequence->getEventPointer (i)->message;
        buffer.addEvent (message, int(message.getTimeStamp ()));

        // get samples per second base on midi file's time-base(ticks) and
        // seconds per quarter note. 
        if (message.isTempoMetaEvent())
        {
           DBG("\n-------------Tempo changed---------------")
           
           DBG("This song's time-base(ticks): " + String(midiFile.getTimeFormat()))
           
           DBG("MIDI's tempo(milliseconds per quarter note): " + String
               (message.getTempoSecondsPerQuarterNote() * 1000))
           
           DBG("Current tempo: " + String(60 / message.getTempoSecondsPerQuarterNote()))

           // this formula very important!!!! I finally got it!!!!!!!!!!!!!
           samples = midiFile.getTimeFormat() / message.getTempoSecondsPerQuarterNote();
        }
      }
    }

    // Start the background thread
    midiOutput->startBackgroundThread();

    // Now send the entire block of messages, have it start 0.05 seconds from now.
    midiOutput->sendBlockOfMessages(buffer, Time::getMillisecondCounter() + 50, samples);
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
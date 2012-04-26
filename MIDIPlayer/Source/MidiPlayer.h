/*
================================================================================
            MIDI Playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// used to playback MIDI file or MIDI data.

#ifndef __MIDIPLAYER_H_
#define __MIDIPLAYER_H_

//==============================================================================
class MidiPlayer
{
public:
    MidiPlayer();
    ~MidiPlayer();

    void selectMidiDevice();

    void playMidi(File& file);
    void stopMidi();

private:
    //==========================================================================
    ScopedPointer<MidiOutput> midiOutput;

//     MidiFile midiFile;
//     const MidiMessageSequence* midiMessageSeque;
//     MidiMessage message;
//     MidiBuffer buffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiPlayer)
};

#endif  // __MIDIPLAYER_H_

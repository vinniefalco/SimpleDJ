/*
================================================================================
            MIDI Playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// control-bar contain by BaseComp.

#ifndef __CONTROLBAR_H_
#define __CONTROLBAR_H_

class MidiPlayer;

//==============================================================================
class ControlBar : public Component, public ButtonListener
{
public:
    ControlBar ();
    ~ControlBar();

    void buttonClicked(Button* button);

private:
    //==========================================================================
    enum {SETUP = 0, OPEN_FILE, PLAY, PAUSE, BACK, ABOUT, BTSNUM};

    OwnedArray<ImageButton> bts;
    MidiPlayer* midiPlayer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlBar)

};

#endif  // __CONTROLBAR_H_

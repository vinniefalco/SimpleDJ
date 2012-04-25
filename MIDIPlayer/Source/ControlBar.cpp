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
#include "ControlBar.h"
#include "HelpAndAbout.h"
#include "MidiPlayer.h"

//===============================================================================

ControlBar::ControlBar () : isPlaying(false)
{  
    // creat and add buttons..
    for (int i = 0, x = 0; i < BTSNUM; ++i, x += 105)
    {
        bts.add(new TextButton());
        addAndMakeVisible(bts[i]);
        bts[i]->addListener(this);
        bts[i]->setBounds(x, 10, 100, 30);
    }

    // properties of individual buttons...
    bts[OPEN_FILE]->setButtonText("Open...");
    bts[PLAY]->setButtonText("Play/Stop");
    bts[ABOUT]->setButtonText("About...");

    // creat midiPlayer..
    midiPlayer = new MidiPlayer();

    setVisible(true); 
    setSize(BTSNUM * 105 - 5, 50);
}
//=================================================================================
ControlBar::~ControlBar()
{
    for (int i = 0; i < BTSNUM; ++i)
        bts[i]->removeListener(this);

    deleteAndZero(midiPlayer);
}
//=================================================================================
void ControlBar::buttonClicked(Button* button)
{
    // setup audio device..
//     if (bts[SETUP] == button)
//     {
//         midiPlayer->selectMidiDevice();
//     }

   // open a midi file..
   if (bts[OPEN_FILE] == button)
   {
      FileChooser fc("Open a MIDI file");

      if (fc.browseForFileToOpen())
      {
         midiFile = fc.getResult();
         midiPlayer->playMidi(midiFile);
         isPlaying = true;
      }
   }

   // playback or stop..
    else if (bts[PLAY] == button)
    {
        if (isPlaying)
        {
            midiPlayer->stopMidi();
            isPlaying = false;
        }
        else
        {
           midiPlayer->playMidi(midiFile);
           isPlaying = true;
        }
    }

    // show about box.
    else if (bts[ABOUT] == button)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, 
            TRANS("About this demo..."), HelpAndAbout::getAboutString());
    }
}


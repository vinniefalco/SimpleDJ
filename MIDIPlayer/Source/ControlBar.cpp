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
   Image img;
   // creat and add buttons..
   for (int i = 0, x = 0; i < BTSNUM; ++i, x += 53)
   {
      bts.add(new ImageButton());
      addAndMakeVisible(bts[i]);
      bts[i]->addListener(this);
      bts[i]->setBounds(x, 1, 48, 48);

      // get each button's image..
      switch(i)
      {
//       case SETUP: 
//          img = ImageCache::getFromMemory(BinaryData::setup_gif, BinaryData::setup_gifSize);
//          break;
      case OPEN_FILE:
         img = ImageCache::getFromMemory(BinaryData::open_gif, BinaryData::open_gifSize);
         break;
      case PLAY:
         img = ImageCache::getFromMemory(BinaryData::play_gif, BinaryData::play_gifSize);
         break;
//       case PAUSE:
//          img = ImageCache::getFromMemory(BinaryData::pause_gif, BinaryData::pause_gifSize);
//          break;
//       case BACK:
//          img = ImageCache::getFromMemory(BinaryData::back_gif, BinaryData::back_gifSize);
//          break;
      case ABOUT:
         img = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
         break;
      default:
         break;
      }

      // set each button's image..
      bts[i]->setImages(false, false, false, 
         img, 1.0f, Colour(0x0), 
         img, 1.0f, Colours::yellow.withAlpha(0.3f), 
         img, 1.0f, Colours::red.withAlpha(0.4f));
   }

   // creat midiPlayer..
   midiPlayer = new MidiPlayer();

   setVisible(true); 
   setSize(BTSNUM * 53 - 5, 50);
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


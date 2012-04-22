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
#include "BaseComp.h"
#include "ControlBar.h"

//===============================================================================

BaseComp::BaseComp ()
{   
    controlBar = new ControlBar();
    addAndMakeVisible(controlBar);

    setSize(600, 380);
    setVisible(true);    
}
//=================================================================================
BaseComp::~BaseComp()
{
}
//=================================================================================
void BaseComp::paint(Graphics& g)
{
    // fill control-bar area..
    g.setColour(Colours::darkcyan);

    g.fillRoundedRectangle(2.0f, float(getHeight() - 50), 
        float(getWidth() - 4), 50.0f, 10.0f);
}
//=================================================================================
void BaseComp::resized()
{  
   controlBar->setBounds((getWidth() - controlBar->getWidth()) / 2, getHeight() - 50, 
       controlBar->getWidth(), controlBar->getHeight());
}

/*
================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "TrackSpace.h"

//===============================================================================

TrackSpace::TrackSpace ()
{   
    // add 8 Buttons...
    for (int i = 0; i < 8; ++i)
    {
        beats.add(new TextButton());
        addAndMakeVisible(beats[i]);
        beats[i]->setClickingTogglesState(true);
        beats[i]->setColour(TextButton::buttonColourId, Colours::lightgrey);
        beats[i]->setColour(TextButton::buttonOnColourId, Colours::green);
        beats[i]->addListener(this);
        beats[i]->setBounds(i * 60, 5, 30, 30);
    }    

    setSize(500, 40);
}
//=================================================================================
TrackSpace::~TrackSpace()
{
}
//=================================================================================
void TrackSpace::paint(Graphics& g)
{
}
//=================================================================================
void TrackSpace::buttonClicked(Button* button)
{

}

/*
================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackPanel.h"
#include "TrackSpace.h"
#include "WorkSpace.h"

//===============================================================================

WorkSpace::WorkSpace ()
{   
    // create, add and setBounds track panles..
    for (int i = 0; i < 6; ++i)
    {
        trackPanle.add(new TrackPanle());
        addAndMakeVisible(trackPanle[i]);

        int y = trackPanle[i]->getHeight();
        trackPanle[i]->setBounds(0, i * (y + 15), trackPanle[i]->getWidth(), y);
    }
    
    // create, add and setBounds track space..
    for (int i = 0; i < 6; ++i)
    {
        trackSpace.add(new TrackSpace());
        addAndMakeVisible(trackSpace[i]);

        int y = trackSpace[i]->getHeight();
        trackSpace[i]->setBounds(140, i * (y + 15), trackSpace[i]->getWidth(), y);
    }
}
//=================================================================================
WorkSpace::~WorkSpace()
{
}
//=================================================================================
void WorkSpace::paint(Graphics& g)
{
    // for demo show..
    g.setColour(Colours::darksalmon);
    g.fillRoundedRectangle(135.0f, 1.0f, float(getWidth() - 140), 39.0f, 10.0f);
}
//=================================================================================



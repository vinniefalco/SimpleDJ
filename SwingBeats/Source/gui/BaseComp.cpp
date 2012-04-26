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
#include "WorkSpace.h"
#include "ControlBar.h"
#include "BaseComp.h"

//===============================================================================

BaseComp::BaseComp ()
{  
    // work space..
    addAndMakeVisible(workSpace = new WorkSpace());

    // MIDI keyboard..
    addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent 
        (keyboardState, MidiKeyboardComponent::horizontalKeyboard));

    // control-bar..
    addAndMakeVisible(controlBar = new ControlBar());
    
    setSize(640, 480);
    setVisible(true);    
}
//=================================================================================
BaseComp::~BaseComp()
{
    deleteAndZero(workSpace);
    deleteAndZero(midiKeyboard);
    deleteAndZero(controlBar);
}
//=================================================================================
void BaseComp::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);

    g.drawRoundedRectangle(150.0f, 15.0f, 
        float(getWidth() - 170), float(getHeight() - 155), 10.0f, 2.0f);
}
//=================================================================================
void BaseComp::resized()
{  
    workSpace->setBounds(20, 20, getWidth() - 40, getHeight() - 130);

    midiKeyboard->setBounds(30, workSpace->getHeight() + 10, getWidth() - 60, 60);

    controlBar->setBounds((getWidth() - controlBar->getWidth()) / 2, getHeight() - 60, 
        controlBar->getWidth(), 60);
   
}
//================================================================================

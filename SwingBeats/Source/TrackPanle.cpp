/*
==========================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackPanle.h"

//========================================================================================

TrackPanle::TrackPanle ()
{   
    // back button..
    DrawablePath drawPath;
    Path p;
    p.clear();
    p.addLineSegment (Line<float>(0.0f, 0.0f, 0.0f, 20.0f), 5.0f);
    p.addTriangle(5.0f, 10.0f, 20.0f, 0.0f, 20.0f, 20.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::black);

    backBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(backBt);
    backBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);    
    backBt->setImages(&drawPath);
    backBt->addListener(this);
    backBt->setBounds(10, 5, 30, 30);

    // back/play button..
    p.clear();
    p.addTriangle(0.0f, 10.0f, 9.0f, 0.0f, 9.0f, 20.0f);
    p.addTriangle(11.0f, 0.0f, 21.0f, 10.0f, 11.0f, 20.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::black);

    backAndPlayBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(backAndPlayBt);
    backAndPlayBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    backAndPlayBt->setImages(&drawPath);
    backAndPlayBt->addListener(this);
    backAndPlayBt->setBounds(backBt->getRight() + 5, 5, 30, 30);

    // keyboard button..
    p.clear();
    p.addLineSegment (Line<float>(5.0f, 0.0f, 5.0f, 30.0f), 1.0f);
    p.addLineSegment (Line<float>(15.0f, 0.0f, 15.0f, 30.0f), 1.0f);
    p.addLineSegment (Line<float>(25.0f, 0.0f, 25.0f, 30.0f), 1.0f);
    p.addLineSegment (Line<float>(5.0f, 0.0f, 5.0f, 20.0f), 10.0f);
    p.addLineSegment (Line<float>(25.0f, 0.0f, 25.0f, 20.0f), 10.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::black);

    keybdBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(keybdBt);
    keybdBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);;
    keybdBt->setImages(&drawPath);
    keybdBt->setClickingTogglesState(true);
    keybdBt->setBackgroundColours (Colours::lightgrey, Colours::darksalmon);
    keybdBt->addListener(this);
    keybdBt->setBounds(backAndPlayBt->getRight() + 5, 5, 30, 30);
    keybdBt->setToggleState(true, false);

    setSize(120, 40);
}
//===========================================================================================
TrackPanle::~TrackPanle()
{
    deleteAndZero(backBt);
    deleteAndZero(backAndPlayBt);
    deleteAndZero(keybdBt);
}
//===========================================================================================
void TrackPanle::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.drawRoundedRectangle(0.0f, 0.0f, float(getWidth()), float(getHeight()), 10.0f, 1.0f);
}
//===========================================================================================
void TrackPanle::buttonClicked(Button* button)
{
}
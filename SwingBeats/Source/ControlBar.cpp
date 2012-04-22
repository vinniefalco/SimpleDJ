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
#include "ControlBar.h"

//===============================================================================

ControlBar::ControlBar () :
        bafenImg(ImageCache::getFromMemory(BinaryData::bafen_png, BinaryData::bafen_pngSize)),
        erfenImg(ImageCache::getFromMemory(BinaryData::erfen_png, BinaryData::erfen_pngSize)),
        wuguiImg(ImageCache::getFromMemory(BinaryData::wugui_png, BinaryData::wugui_pngSize)),
        tuziImg(ImageCache::getFromMemory(BinaryData::tuzi_png, BinaryData::tuzi_pngSize))
{  
    // time change slider..
    addAndMakeVisible(timeSld = new Slider());
    timeSld->setRange(1.0, 8.0, 1.0);
    timeSld->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    timeSld->setPopupMenuEnabled (true);
    timeSld->addListener(this);
    timeSld->setBounds(30, 20, 140, 20); 

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
    backBt->setBounds(timeSld->getRight() + 30, 15, 30, 30);

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
    backAndPlayBt->setBounds(backBt->getRight() + 5, 15, 30, 30);

    // help button..
    p.clear();
    p.addStar (Point<float>(), 5, 16.0f, 30.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::red);

    helpBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(helpBt);
    helpBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);;
    helpBt->setImages(&drawPath);
    helpBt->addListener(this);
    helpBt->setBounds(backAndPlayBt->getRight() + 5, 15, 30, 30);

    // stop button..
    p.clear();
    p.addRectangle(5.0f, 5.0f, 20.0f, 20.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::black);

    stopBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(stopBt);
    stopBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    stopBt->setImages(&drawPath);
    stopBt->addListener(this);
    stopBt->setBounds(helpBt->getRight() + 5, 15, 30, 30);    

    // paly button..
    p.clear();
    p.addTriangle(1.0f, 0.0f, 20.0f, 10.0f, 1.0f, 20.0f);
    drawPath.setPath(p);
    drawPath.setFill(Colours::black);

    playBt = new DrawableButton(String::empty, DrawableButton::ImageOnButtonBackground);
    addAndMakeVisible(playBt);
    playBt->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);    
    playBt->setClickingTogglesState(true);
    playBt->setImages(&drawPath);
    playBt->setBackgroundColours (Colours::lightgrey, Colours::darksalmon);
    playBt->addListener(this);
    playBt->setToggleState(true,false);
    playBt->setBounds(stopBt->getRight() + 5, 15, 30, 30);

    // tempo slider..
    addAndMakeVisible(tempoSld = new Slider());
    tempoSld->setRange(10.0, 200.0, 5.0);
    tempoSld->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    tempoSld->setPopupMenuEnabled (true);
    tempoSld->addListener(this);
    tempoSld->setBounds(playBt->getRight() + 40, 20, 140, 20); 
    
    setVisible(true); 
    setSize(tempoSld->getRight() + 30, 60);
}
//=================================================================================
ControlBar::~ControlBar()
{
    deleteAndZero(timeSld);
    deleteAndZero(tempoSld);
    deleteAndZero(backBt);
    deleteAndZero(backAndPlayBt);
    deleteAndZero(helpBt);
    deleteAndZero(stopBt);
    deleteAndZero(playBt);    
}
//=================================================================================
void ControlBar::paint(Graphics& g)
{
    g.drawImageWithin(bafenImg, 0, 0, 25, 60, RectanglePlacement::centred);    
    g.drawImageWithin(erfenImg, timeSld->getRight() + 3, 0, 25, 60, RectanglePlacement::centred);
    g.drawImageWithin(wuguiImg, playBt->getRight() + 10, 0, 25, 60, RectanglePlacement::centred);
    g.drawImageWithin(tuziImg, tempoSld->getRight() + 5, 0, 25, 60, RectanglePlacement::centred);    
}
//=================================================================================
void ControlBar::buttonClicked(Button* button)
{

}
//=================================================================================
void ControlBar::sliderValueChanged(Slider* slider)
{

}
/*
==========================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================
*/

// base component contain by main window.

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "BaseComp.h"
#include "HelpAndAbout.h"

//=========================================================================

BaseComp::BaseComp () : 
        s(MemoryBlock(BinaryData::trans_cn, BinaryData::trans_cnSize).toString())
{
    // chessboard..
    addAndMakeVisible(chessboard = new Chessboard(this));

    // info label..
    addAndMakeVisible(infoLb = new Label());
    infoLb->setFont(Font(22.0f, Font::bold));
    infoLb->setColour(Label::textColourId, Colours::lightgrey);
    infoLb->setText("0 : 0", false);
    infoLb->setJustificationType(Justification::centred);

    // set timeout combobox..
    addAndMakeVisible(timeSetCb = new ComboBox());
    timeSetCb->setColour(ComboBox::backgroundColourId, Colours::lightblue);   
    timeSetCb->addItem(TRANS("Unlimited"), 1);
    timeSetCb->addSeparator();

    for (int i = 2; i < 13; ++i)
    {
        timeSetCb->addItem (String(i * 5) + TRANS(" seconds"), i);
    }

    timeSetCb->addListener(this);
    timeSetCb->setSelectedId (1);    

    // set round combobox..
    addAndMakeVisible(roundSetCb = new ComboBox());
    roundSetCb->setColour(ComboBox::backgroundColourId, Colours::lightblue);
    roundSetCb->addItem(TRANS("Unlimited"), 1);
    roundSetCb->addSeparator();

    for (int i = 2; i < 9; ++i)
    {
        roundSetCb->addItem (String(i * 6 + 6) + TRANS(" steps"), i);
    }

    roundSetCb->addListener(this);
    roundSetCb->setSelectedId (1);

    // combobox's label..
    addAndMakeVisible(timeSetLb = new Label());
    timeSetLb->setColour(Label::textColourId, Colours::lightgrey);

    addAndMakeVisible(roundSetLb = new Label());
    roundSetLb->setColour(Label::textColourId, Colours::lightgrey);

    // hint button..
    addAndMakeVisible(hintBt = new TextButton("H"));
    hintBt->setColour(TextButton::buttonColourId, Colours::beige);
    hintBt->setColour(TextButton::buttonOnColourId, Colours::lightgreen);
    hintBt->addShortcut(KeyPress('h'));
    hintBt->setClickingTogglesState(true);
    hintBt->addListener(this);

    // languge button..
    addAndMakeVisible(langugeBt = new TextButton("L"));
    langugeBt->setColour(TextButton::buttonColourId, Colours::beige);
    langugeBt->setColour(TextButton::buttonOnColourId, Colours::lightgreen);
    langugeBt->addShortcut(KeyPress('l'));
    langugeBt->setClickingTogglesState(true);
    langugeBt->addListener(this);

    // help button..
    addAndMakeVisible(helpBt = new TextButton("?"));
    helpBt->addShortcut(KeyPress('?'));
    helpBt->setColour(TextButton::buttonColourId, Colours::beige);
    helpBt->addListener(this);

    // about button..
    addAndMakeVisible(aboutBt = new TextButton("A"));
    aboutBt->addShortcut(KeyPress('a'));
    aboutBt->setColour(TextButton::buttonColourId, Colours::beige);
    aboutBt->addListener(this);
    
    resetText();
        
    setSize(640, 480);
    setVisible(true);
}
//===========================================================================
BaseComp::~BaseComp()
{
    deleteAndZero(infoLb);
    deleteAndZero(timeSetLb);
    deleteAndZero(timeSetCb);
    deleteAndZero(roundSetLb);
    deleteAndZero(roundSetCb);
    deleteAndZero(aboutBt);
    deleteAndZero(hintBt);
    deleteAndZero(langugeBt);
    deleteAndZero(helpBt);
}
//===========================================================================
void BaseComp::resized()
{
    // info label..
    infoLb->setBounds(getWidth() / 2 - 140, 5, 280, 30);

    // buttons..
    hintBt->setBounds(10, getHeight() - 40, 30, 30);
    langugeBt->setBounds(hintBt->getRight() + 5, hintBt->getY(), 30, 30);
    helpBt->setBounds(getWidth() - 80, getHeight() - 40, 30, 30);
    aboutBt->setBounds(helpBt->getRight() + 10, getHeight() - 40, 30, 30);

    // get chessboard size, set its width == height and auto centre..
    int size = jmin(getWidth(), getHeight()) - 80;

    if (chessboard != nullptr)
    {
        chessboard->centreWithSize(size, size);
    }

    // combobox..
    roundSetCb->setBounds(getWidth() / 2 - 100, getHeight() - 30, 90, 20);
    roundSetLb->attachToComponent(roundSetCb,true);

    timeSetCb->setBounds(roundSetCb->getRight() + 90, getHeight() - 30, 90, 20);
    timeSetLb->attachToComponent(timeSetCb, true);    
}
//==========================================================================
void BaseComp::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    // set timeout..
    if (comboBoxThatHasChanged == timeSetCb) 
    {
        if (1 == timeSetCb->getSelectedId()) 
        {
            chessboard->setTimeout(0);
        }
        else
        {
            chessboard->setTimeout(timeSetCb->getSelectedId() * 5);
        }
        
    }
    // set limit steps..
    else if (comboBoxThatHasChanged == roundSetCb)
    {
        if (1 == roundSetCb->getSelectedId())
        {
            chessboard->setSteps(0); 
        }
        else
        {
            chessboard->setSteps((roundSetCb->getSelectedId() - 2) * 6 + 18); 
        }        
    }
}
//==========================================================================
void BaseComp::buttonClicked(Button* button)
{
    if (button == aboutBt)     // show about info..
    {
        chessboard->stopTimer();  

        AlertWindow::showMessageBox (AlertWindow::InfoIcon, TRANS("About..."), 
            HelpAndAbout::getAboutString());

        chessboard->resetThinkTime();
        chessboard->startTimer(200);
    }

    else if (button == helpBt)   // show help..
    {
        chessboard->stopTimer();  

        AlertWindow::showMessageBox (AlertWindow::QuestionIcon, TRANS("Help..."), 
            HelpAndAbout::getHelpString());

        chessboard->resetThinkTime();
        chessboard->startTimer(200);
    }
    
    // show or don't show hint (first chess piece has underline).
    else if (button == hintBt)
    {
        chessboard->setFirst(getHintState());
    }
       
    else if (button == langugeBt)   // switch languge..
    {
        if (langugeBt->getToggleState())
        {  
            LocalisedStrings::setCurrentMappings(new LocalisedStrings(s));
        }
        else
        {
            LocalisedStrings::setCurrentMappings(nullptr);
        }

        resetText();
    }
}
//==========================================================================
// update info label's text that on top of window.
void BaseComp::setInfo()
{    
    infoLb->setText(chessboard->getInfo(), false);
}
//==========================================================================
// for trans widgets' text...
void BaseComp::resetText()
{
    // timeout combobox...
    timeSetCb->clear(true);
    timeSetCb->addItem(TRANS("Unlimited"), 1);
    timeSetCb->addSeparator();

    for (int i = 2; i < 13; ++i)
    {
        timeSetCb->addItem (String(i * 5) + TRANS(" seconds"), i);
    }

    const int timeoutIndex = chessboard->getTimeout();

    if (0 == timeoutIndex)
        timeSetCb->setSelectedId(1);         
    else
        timeSetCb->setSelectedId(timeoutIndex / 5);         

    // steps combobox...
    roundSetCb->clear(true);
    roundSetCb->addItem(TRANS("Unlimited"), 1);
    roundSetCb->addSeparator();

    for (int i = 2; i < 9; ++i)
    {
        roundSetCb->addItem (String(i * 6 + 6) + TRANS(" steps"), i);
    }

    const int stepsIndex = chessboard->getSteps();

    if (0 == stepsIndex)
        roundSetCb->setSelectedId (1);
    else
        roundSetCb->setSelectedId(stepsIndex / 6 - 1);

    // labels..
    timeSetLb->setText(TRANS("Timeout: "), false);
    roundSetLb->setText(TRANS("Limit step: "), false);

    // buttons' tool tips..
    aboutBt->setTooltip(TRANS("Show About info: ") + " [A]");
    hintBt->setTooltip(TRANS("Real-time Prompts: ") + " [H]");
    langugeBt->setTooltip(TRANS("Switch languge: ") + " [L]");
    helpBt->setTooltip(TRANS("Get help: ") + " [?]");
}

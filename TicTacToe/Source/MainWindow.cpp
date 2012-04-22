/*
==========================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "BaseComp.h"

//========================================================================
MainAppWindow::MainAppWindow() : DocumentWindow (
    ProjectInfo::projectName, Colours::black, DocumentWindow::allButtons)
{
    centreWithSize (640, 480);
    setVisible (true);
    setResizable(true, false);
    setResizeLimits (540, 380, 4096, 4096);
    
    // buttons on most left of title-bar..
    setTitleBarButtonsRequired(DocumentWindow::allButtons, true);
    setContentOwned (new BaseComp(), true);

    // translucent window.
    setAlpha(0.75f);
}

MainAppWindow::~MainAppWindow()
{
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

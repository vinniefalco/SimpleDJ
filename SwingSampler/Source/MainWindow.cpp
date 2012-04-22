/*
  ==============================================================================
         S-Sampler

  Author: SwingCoder
  Email: SwingCoder2@gmail.com
  Github: https://github.com/SwingCoder

  License: MIT License, Copyright (c) 2012 by SwingCoder
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "BaseComp.h"

//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
{
    centreWithSize (900, 600);
    setVisible (true);
    setResizable(true, false);
    setResizeLimits (665, 485, 4096, 4096);

    // buttons on most left of title-bar..
    setTitleBarButtonsRequired(DocumentWindow::allButtons, true);
    setContentOwned (new BaseComp(), true);
}

MainAppWindow::~MainAppWindow()
{
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

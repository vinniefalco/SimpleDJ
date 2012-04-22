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
#include "MainWindow.h"
#include "BaseComp.h"

//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::closeButton | DocumentWindow::minimiseButton)
{
    centreWithSize (640, 480);
    setVisible (true);
    setResizable(false, false);

    setTitleBarButtonsRequired
        (DocumentWindow::closeButton | DocumentWindow::minimiseButton, true);
    
    setContentOwned (new BaseComp(), true);
}
//==============================================================================
MainAppWindow::~MainAppWindow()
{
}
//==============================================================================
void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

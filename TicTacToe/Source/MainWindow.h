/*
==========================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================
*/

// main window frame..

#ifndef __MAINAPPWINDOW_H_
#define __MAINAPPWINDOW_H_

//=======================================================================
class MainAppWindow : public DocumentWindow
{
public:
    //===================================================================
    MainAppWindow();
    ~MainAppWindow();

    void closeButtonPressed();

private:
    //===================================================================
    TooltipWindow toolTips;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
};


#endif  // __MAINAPPWINDOW_H_

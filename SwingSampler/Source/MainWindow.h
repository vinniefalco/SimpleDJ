/*
  ==============================================================================
        S-Sampler

  Author: SwingCoder
  Email: SwingCoder2@gmail.com
  Github: https://github.com/SwingCoder

  License: MIT License, Copyright (c) 2012 by SwingCoder
  ==============================================================================
*/

// application's main frame..

#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_

//==============================================================================
class MainAppWindow : public DocumentWindow
{
public:
    //==============================================================================
    MainAppWindow();
    ~MainAppWindow();

    void closeButtonPressed();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
};

#endif  // __MAINWINDOW_H_

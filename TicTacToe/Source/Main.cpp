/*
==========================================================================
        Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
==========================================================================
*/

// start this application..

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//========================================================================
class TicTacToeApplication  : public JUCEApplication
{
public:
    //====================================================================
    TicTacToeApplication()
    {
    }

    ~TicTacToeApplication()
    {
    }

    //=====================================================================
    void initialise (const String& /*commandLine*/)
    {
        LookAndFeel::getDefaultLookAndFeel().
            setDefaultSansSerifTypefaceName(L"Î¢ÈíÑÅºÚ");
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        mainWindow = 0;
    }

    //=====================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //=====================================================================
    const String getApplicationName()
    {
        return ProjectInfo::projectName;
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& /*commandLine*/)
    {
        
    }

private:
    ScopedPointer <MainAppWindow> mainWindow;
};

//======================================================================
START_JUCE_APPLICATION(TicTacToeApplication)

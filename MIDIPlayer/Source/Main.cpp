/*
================================================================================
            MIDI Playback

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//==============================================================================
class MIDIPlayerApplication  : public JUCEApplication
{
public:
    //==============================================================================
    MIDIPlayerApplication()
    {
    }

    ~MIDIPlayerApplication()
    {
    }

    //==============================================================================
    void initialise (const String& /*commandLine*/)
    {
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        mainWindow = 0;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return "MIDI Player";
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

//==============================================================================
START_JUCE_APPLICATION(MIDIPlayerApplication)

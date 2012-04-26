/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "CallbackQueue.h"
#include "MidiSequencer.h"

//==================================================================================

MidiSequencer::MidiSequencer(CallbackQueue* _guiCall) : Thread("seqThread"), 
    guiCallbackQueue(_guiCall)
{

}

//==================================================================================
MidiSequencer::~MidiSequencer()
{

}

//==================================================================================
void MidiSequencer::addListener( Listener* listener )
{
    listenerList.add(guiCallbackQueue);
}

//==================================================================================
void MidiSequencer::removeListener( Listener* listener )
{
    listenerList.remove(guiCallbackQueue);
}

//==================================================================================
void MidiSequencer::run()
{
    
}

//==================================================================================
void MidiSequencer::setTempo( float bpm )
{

}

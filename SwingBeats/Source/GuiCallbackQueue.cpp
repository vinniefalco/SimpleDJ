/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CallbackQueue.h"
#include "GuiCallbackQueue.h"

//==================================================================================

GuiCallbackQueue::GuiCallbackQueue()
{
}

//==================================================================================

GuiCallbackQueue::~GuiCallbackQueue()
{
}

//==================================================================================

void GuiCallbackQueue::handleAsyncUpdate()
{
    process();
}

//==================================================================================

void GuiCallbackQueue::signal()
{
    triggerAsyncUpdate();
}

//==================================================================================

void GuiCallbackQueue::reset()
{
}



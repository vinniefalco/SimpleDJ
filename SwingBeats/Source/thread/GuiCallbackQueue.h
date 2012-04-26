/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef _GUICALLBACKQUEUE_H_
#define _GUICALLBACKQUEUE_H_

class CallbackQueue;
//==================================================================================
class GuiCallbackQueue : public AsyncUpdater, public CallbackQueue
{
public:
    GuiCallbackQueue();
    ~GuiCallbackQueue();

    void handleAsyncUpdate();

    void signal();
    void reset();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiCallbackQueue)
};



#endif // _GUICALLBACKQUEUE_H_
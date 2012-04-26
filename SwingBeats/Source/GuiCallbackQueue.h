/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef GUICALLBACKQUEUE_H_
#define GUICALLBACKQUEUE_H_

class GuiCallbackQueue : public AsyncUpdater, public CallbackQueue
{
public:
    GuiCallbackQueue();
    ~GuiCallbackQueue();

    virtual void handleAsyncUpdate();

    virtual void signal();
    virtual void reset();


};



#endif // GUICALLBACKQUEUE_H_
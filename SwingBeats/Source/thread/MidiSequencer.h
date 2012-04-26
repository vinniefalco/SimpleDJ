/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef _MIDISEQUENCER_H_
#define _MIDISEQUENCER_H_

class CallbackQueue;
//==================================================================================
class MidiSequencer : public Thread
{
public:
    MidiSequencer(CallbackQueue* _guiCall);
    ~MidiSequencer();

    struct Listener 
    {
        void onSBBeat();
    };

    void addListener (Listener* listener);
    void removeListener (Listener* listener);

    void run();

    void setTempo (float bpm);

private:
    CallbackQueue* guiCallbackQueue;
    ListenerList<CallbackQueue> listenerList;
    WaitableEvent waitableEvent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSequencer)
};

#endif // _MIDISEQUENCER_H_

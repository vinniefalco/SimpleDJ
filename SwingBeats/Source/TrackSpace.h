/*
================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// this component contain by WorkSpace component.

#ifndef __TRACKSPACE_H_
#define __TRACKSPACE_H_

//==============================================================================
class TrackSpace : public Component, public ButtonListener
{
public:
    TrackSpace ();
    ~TrackSpace();

    void paint(Graphics& g);
    void buttonClicked(Button* button);

private:
    //==========================================================================
    OwnedArray<TextButton> beats;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackSpace)
};

#endif  // __TRACKSPACE_H_

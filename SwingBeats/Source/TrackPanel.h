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

#ifndef __TRACKPANLE_H_
#define __TRACKPANLE_H_

//==============================================================================
class TrackPanle : public Component, public ButtonListener
{
public:
    TrackPanle ();
    ~TrackPanle();

    void paint(Graphics& g);
    void buttonClicked(Button* button);

private:
    //==========================================================================
    DrawableButton* backBt; 
    DrawableButton* backAndPlayBt;
    DrawableButton* keybdBt;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackPanle)
};

#endif  // __TRACKPANLE_H_

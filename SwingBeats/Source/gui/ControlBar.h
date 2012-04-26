/*
================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// control-bar contain by BaseComp.

#ifndef __CONTROLBAR_H_
#define __CONTROLBAR_H_

//==============================================================================
class ControlBar : public Component,
    public ButtonListener,
    public SliderListener
{
public:
    ControlBar ();
    ~ControlBar();

    void paint(Graphics& g);

    void buttonClicked(Button* button);
    void sliderValueChanged(Slider* slider);

private:
    //==========================================================================
    Image bafenImg, erfenImg, wuguiImg, tuziImg;

    DrawableButton* backBt; 
    DrawableButton* backAndPlayBt;
    DrawableButton* helpBt;
    DrawableButton* stopBt;
    DrawableButton* playBt;
    
    Slider* timeSld;
    Slider* tempoSld;   
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlBar)
};

#endif  // __CONTROLBAR_H_

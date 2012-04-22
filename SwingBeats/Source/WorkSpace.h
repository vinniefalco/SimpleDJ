/*
================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// this component contain by base component.

#ifndef __WORKSPACE_H_
#define __WORKSPACE_H_

class TrackPanle;
class TrackSpace;

//==============================================================================
class WorkSpace : public Component
{
public:
    WorkSpace ();
    ~WorkSpace();

    void paint(Graphics& g);

private:
    //==========================================================================
    OwnedArray<TrackPanle> trackPanle;
    OwnedArray<TrackSpace> trackSpace;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WorkSpace)
};

#endif  // __WORKSPACE_H_

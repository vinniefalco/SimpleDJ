/*
================================================================================
            Tic Tac Toe

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// base component contain by main window.

#ifndef __BASECOMP_H_
#define __BASECOMP_H_

#include "Chessboard.h"

//==============================================================================
class BaseComp : public Component, 
    public ComboBoxListener, 
    public ButtonListener
{
public:
    BaseComp ();
    ~BaseComp();

    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked(Button* button);

    // update info label's text that on top of window.
    void setInfo();
    const bool getHintState() const { return hintBt->getToggleState(); }

private:
    //==========================================================================
    void resetText();

    const String s;

    ScopedPointer<Chessboard> chessboard;

     Label* infoLb;
     Label* timeSetLb;
     Label* roundSetLb;

     ComboBox* timeSetCb;
     ComboBox* roundSetCb;

     TextButton* hintBt;
     TextButton* langugeBt;
     TextButton* aboutBt;
     TextButton* helpBt;
     
     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseComp)
};

#endif  // __BASECOMP_H_

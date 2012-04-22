/*
================================================================================
            S-Sampler

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

// base component contain by main window.

#ifndef __BASECOMP_H_
#define __BASECOMP_H_

class SamplerSource;
//==============================================================================
class BaseComp : public Component, 
    public ComboBoxListener,
    public ButtonListener,
    public FileDragAndDropTarget
{
public:
    BaseComp ();
    ~BaseComp();

    void paint(Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBox);
    void buttonClicked(Button* button);

    // file drag and drop..
    bool isInterestedInFileDrag (const StringArray&){return true;}
    void filesDropped (const StringArray& filenames, int, int);

public:
    //==========================================================================
    ComboBox* toneSetCb;
    ComboBox* rootSetCb;
    Label* fileInfoLb;

private:
    //==========================================================================
    void loadAudioFile();

    // set widgets' text for switch languge in real-time
    void resetText();  

    AudioDeviceManager deviceManager;
    AudioSourcePlayer sourcePlayer;
    ScopedPointer<SamplerSource> samplerSource; 

    MidiKeyboardComponent* midiKeyboard;
    MidiKeyboardState keyboardState;

    ScopedPointer<AudioDeviceSelectorComponent> selector;
    
    Label* sltLb; 
    Label* rootLb;
    TextButton* setupBt;
    TextButton* loadBt;
    TextButton* unloadBt;
    TextButton* aboutBt;
    TextButton* langBt;

    String s;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseComp)
};

#endif  // __BASECOMP_H_

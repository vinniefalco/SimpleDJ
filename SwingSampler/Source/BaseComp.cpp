/*
================================================================================
            S-Sampler

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SamplerSource.h"
#include "BaseComp.h"

//===============================================================================

BaseComp::BaseComp () : selector (nullptr),
        s(MemoryBlock(BinaryData::trans_cn, BinaryData::trans_cnSize).toString())
{
    // set languge..
    LocalisedStrings::setCurrentMappings(new LocalisedStrings(s));

    // MIDI keyboard..
    addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent 
        (keyboardState, MidiKeyboardComponent::horizontalKeyboard));

    // sampler source..
    samplerSource = new SamplerSource (keyboardState, this);
    sourcePlayer.setSource (samplerSource);

    // audio device init and add callback..
    deviceManager.initialise(0, 2, nullptr, true);
    deviceManager.addAudioCallback(&sourcePlayer);
    deviceManager.addMidiInputCallback (String::empty, &(samplerSource->midiCollector)); 

    // select instrument combobox and its label..
    addAndMakeVisible(toneSetCb = new ComboBox());
    toneSetCb->setColour(ComboBox::backgroundColourId, Colours::lightblue); 
    toneSetCb->addItem(TRANS("Sine Wave"), 1);
    toneSetCb->addItem(TRANS("Grand Piano"), 2);
    toneSetCb->addItem(TRANS("Solo Viola"), 3);
    toneSetCb->addItem(TRANS("Drum Taiko"), 4);
    toneSetCb->addListener(this);
    toneSetCb->setSelectedId (1);  

    addAndMakeVisible(sltLb = new Label());
    sltLb->attachToComponent(toneSetCb, true);

    // select root MIDI note combobox and its label...
    addAndMakeVisible(rootSetCb = new ComboBox());
    rootSetCb->setColour(ComboBox::backgroundColourId, Colours::lightblue); 

    char note = 'A';
    
    for (int i = 1, oct = 2; i < 20; ++i, ++note)
    {
        if ('H' == note)
            note = 'A';
        
        if ('C' == note)
            ++oct;

        rootSetCb->addItem(note + String(oct), i);
    }

    rootSetCb->addListener(this);
    rootSetCb->setSelectedId (10);
    rootSetCb->setEnabled(false);

    addAndMakeVisible(rootLb = new Label());
    rootLb->attachToComponent(rootSetCb, true);

    // setup audio device button..
    addAndMakeVisible(setupBt = new TextButton());
    setupBt->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    setupBt->setClickingTogglesState(true);
    setupBt->setColour (TextButton::buttonColourId, Colours::lightgrey);
    setupBt->setColour (TextButton::buttonOnColourId, Colours::lightgreen);
    setupBt->addListener(this);

    // load an audio file button..
    addAndMakeVisible(loadBt = new TextButton());
    loadBt->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    loadBt->setColour (TextButton::buttonColourId, Colours::lightgrey);
    loadBt->addListener(this);

    // unload audio file..
    addAndMakeVisible(unloadBt = new TextButton());
    unloadBt->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    unloadBt->setColour (TextButton::buttonColourId, Colours::lightgrey);
    unloadBt->addListener(this);

    // about button..
    addAndMakeVisible(aboutBt = new TextButton());
    aboutBt->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    aboutBt->setClickingTogglesState(true);
    aboutBt->setColour (TextButton::buttonColourId, Colours::lightgrey);
    aboutBt->setColour (TextButton::buttonOnColourId, Colours::lightgreen);
    aboutBt->addListener(this);

    // switch languge button..
    addAndMakeVisible(langBt = new TextButton());
    langBt->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    langBt->setClickingTogglesState(true);
    langBt->setColour (TextButton::buttonColourId, Colours::lightgrey);
    langBt->setColour (TextButton::buttonOnColourId, Colours::lightgreen);
    langBt->setToggleState(true, false);
    langBt->addListener(this);

    // show file info label..
    addAndMakeVisible(fileInfoLb = new Label());
    fileInfoLb->setColour(Label::backgroundColourId, Colour(0x0));

    // the selector to setup audio device..    
    addAndMakeVisible(selector = new AudioDeviceSelectorComponent
        (deviceManager, 0, 255, 0, 255, true, false, true, false));

    selector->setVisible(false);
        
    resetText();

    setSize(900, 600);
    setVisible(true);    
}
//=================================================================================
BaseComp::~BaseComp()
{
    sourcePlayer.setSource(nullptr);
    deviceManager.removeAudioCallback(&sourcePlayer);
    deviceManager.removeMidiInputCallback(String::empty, &(samplerSource->midiCollector));

    deleteAndZero(toneSetCb);
    deleteAndZero(sltLb);
    deleteAndZero(setupBt);
    deleteAndZero(midiKeyboard);
    deleteAndZero(rootSetCb);
    deleteAndZero(rootLb);
    deleteAndZero(loadBt);
    deleteAndZero(unloadBt);
    deleteAndZero(aboutBt);
    deleteAndZero(langBt);
    deleteAndZero(fileInfoLb);
}
//=================================================================================
void BaseComp::paint(Graphics& g)
{
    // background image..
    Image img = ImageCache::getFromMemory
        (BinaryData::bg_jpg, BinaryData::bg_jpgSize);

    g.drawImageWithin(img, 0, 30, getWidth(), getHeight() - 108, 
        RectanglePlacement::stretchToFit);

    // fill background of selector or about info..
    if (setupBt->getToggleState() || aboutBt->getToggleState())
    {
        g.setColour(Colours::lightgrey.withAlpha(0.75f));
        g.fillRect(0, 30, getWidth(), getHeight() - 105);
    }

    // draw about info..
    if (aboutBt->getToggleState())
    {
        g.setColour(Colours::brown);
        g.setFont(65.0f, Font::italic | Font::bold);
        
        g.drawText(TRANS("Swing Sampler"), 20, (getHeight() - 350) / 2 - 60, 
            getWidth() - 40, 300, Justification::centred, false);

        g.setFont(35.0f, Font::bold);

        g.drawText(TRANS("Author: SwingCoder"), 20, (getHeight() - 350) / 2 + 20, 
            getWidth() - 40, 300, Justification::centred, false);

        g.drawText("miti-net@126.com", 20, (getHeight() - 350) / 2 + 70, 
            getWidth() - 40, 300, Justification::centred, false);
    }
}
//=================================================================================
void BaseComp::resized()
{  
    midiKeyboard->setBounds(0, getHeight() - 75, getWidth(), 75); 

    // button and combobox..
    setupBt->setBounds(2, 2, 55, 25);
    toneSetCb->setBounds(setupBt->getRight() + 55, 2, 120, 25);  
    rootSetCb->setBounds(toneSetCb->getRight() + 50, 2, 50, 25);
    loadBt->setBounds(rootSetCb->getRight() + 5, 2, 65, 25);
    unloadBt->setBounds(loadBt->getRight() + 5, 2, 55, 25);
    aboutBt->setBounds(unloadBt->getRight() + 5, 2, 55, 25);
    langBt->setBounds(aboutBt->getRight() + 5, 2, 60, 25);

    // file info label..
    fileInfoLb->setBounds(langBt->getRight() + 5, 2, 
        getWidth() - langBt->getRight() - 5, 25);

    // the selector to setup audio device..
    selector->setBounds((getWidth() - 500) / 2, (getHeight() - 350) / 2, 500, 500);
}
//================================================================================
void BaseComp::comboBoxChanged (ComboBox* comboBox)
{    
    if (comboBox == toneSetCb) // set tone..
    {
        switch (toneSetCb->getSelectedId())
        {
        case 1:
            samplerSource->setSampledSound(SamplerSource::SINEWAVE);
            fileInfoLb->setText(TRANS("Sine Wave"), false);
            break;

        case 2:
            samplerSource->setSampledSound(SamplerSource::PIANO);
            fileInfoLb->setText(TRANS("Grand Piano"), false);
            break;

        case 3:
            samplerSource->setSampledSound(SamplerSource::VIOLA);
            fileInfoLb->setText(TRANS("Solo Viola"), false);
            break;

        case 4:
            samplerSource->setSampledSound(SamplerSource::TAIKO);
            fileInfoLb->setText(TRANS("Drum TaiKo"), false);
            break;

        default:
            fileInfoLb->setText(String::empty, false);
            break;
        }
    }
    else if (comboBox == rootSetCb)
    {
        int noteNumber = 0;

        switch (rootSetCb->getSelectedId())
        {
        case 1:  noteNumber = 57; break;  // A2
        case 2:  noteNumber = 59; break;  // B2
        case 3:  noteNumber = 60; break;  // C3
        case 4:  noteNumber = 62; break;  // D3
        case 5:  noteNumber = 64; break;  // E3
        case 6:  noteNumber = 65; break;  // F3
        case 7:  noteNumber = 67; break;  // G3
        case 8:  noteNumber = 69; break;  // A3
        case 9:  noteNumber = 71; break;  // B3
        case 10: noteNumber = 72; break;  // C4
        case 11: noteNumber = 74; break;  // D4
        case 12: noteNumber = 76; break;  // E4
        case 13: noteNumber = 77; break;  // F4
        case 14: noteNumber = 79; break;  // G4
        case 15: noteNumber = 81; break;  // A4
        case 16: noteNumber = 83; break;  // B4
        case 17: noteNumber = 84; break;  // C5
        case 18: noteNumber = 86; break;  // D5
        case 19: noteNumber = 88; break;  // E5

        default: noteNumber = 72; break;  // C4
        }

        samplerSource->loadSound(noteNumber);
    }
}
//=================================================================================
void BaseComp::buttonClicked(Button* button)
{
    if (button == setupBt)  // show setup audio device..
    {
        if (aboutBt->getToggleState())
        {
            aboutBt->setToggleState(false, false);
        }

        selector->setVisible(setupBt->getToggleState());

        repaint();
    }
    else if (button == loadBt)  // load audio file..
    {
        loadAudioFile();        
    }
    else if (button == unloadBt)    // reset..
    {
        toneSetCb->setEnabled(true);
        toneSetCb->setSelectedId(1);
        rootSetCb->setSelectedId(10);
        fileInfoLb->setText(TRANS("Sine Wave"), false);
        samplerSource->setSampledSound(SamplerSource::SINEWAVE);
    }
    else if (button == aboutBt)  // show about info..
    {
        if (setupBt->getToggleState())
        {
            setupBt->setToggleState(false, false);
            selector->setVisible(false);
        }

        repaint();
    }
    else if (button == langBt)   // switch languge..
    {
        if (langBt->getToggleState()) 
            LocalisedStrings::setCurrentMappings(new LocalisedStrings(s));
        else
            LocalisedStrings::setCurrentMappings(nullptr);

        resetText();    // set widgets' text..
        repaint();
    }
}
//=================================================================================
void BaseComp::filesDropped (const StringArray& filenames, int, int)
{
    const File thisFile (filenames[0]);
    samplerSource->setSampledSound(thisFile);
}
//=================================================================================
void BaseComp::loadAudioFile()
{
    FileChooser fc (TRANS("Open an audio file..."), 
        File::getSpecialLocation (File::userHomeDirectory), "*.wav; *.mp3; *.ogg;" 
        "*.aif; *.aiff; *.wma; *.flac; *.bwf; *.asf; *.m4a; *.wmv; *.wm", 
        true);

    if (fc.browseForFileToOpen()) 
        samplerSource->setSampledSound(fc.getResult());
}
//==================================================================================
// set widgets' text for switch languge in real-time..
void BaseComp::resetText()
{
    sltLb->setText(TRANS("Preset: "), false);
    rootLb->setText(TRANS("Root: "), false);

    setupBt->setButtonText(TRANS("Setup"));
    loadBt->setButtonText(TRANS("Load..."));
    unloadBt->setButtonText(TRANS("Reset"));
    aboutBt->setButtonText(TRANS("About"));
    langBt->setButtonText(TRANS("Languge"));
}

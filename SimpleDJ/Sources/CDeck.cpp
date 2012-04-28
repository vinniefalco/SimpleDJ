/*
  ==============================================================================

  Copyright (c) 2012 by Vinnie Falco

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#include "StandardIncludes.h"
#include "CDeck.h"
#include "CParamToggleButton.h"
#include "CSpeedControl.h"
#include "FileManager.h"

CDeck::CDeck (int deckNumber, Mixer& mixer)
  : vf::ResizableLayout (this)
  , m_deck (Deck::New (mixer.getThread ()))
  , m_hasDropFocus (false)
{
  // Add the Deck to the Mixer.
  mixer.addSource (m_deck);

  setOpaque (true);
  setSize (500, 300);
  
  setMinimumSize (200, 100);

  // Metadata

  m_title = new Label;
  m_title->setFont (24);
  m_title->setColour (Label::textColourId, Colours::orange);
  m_title->setColour (Label::backgroundColourId, Colours::black.withAlpha (.1f));
  m_title->setJustificationType (Justification::left);
  m_title->setBounds (4, 4, 458, 32);
  addToLayout (m_title, anchorTopLeft, anchorTopRight);
  addAndMakeVisible (m_title);

  m_artist = new Label;
  m_artist->setFont (14);
  m_artist->setColour (Label::textColourId, Colours::orange);
  m_artist->setColour (Label::backgroundColourId, Colours::black.withAlpha (.1f));
  m_artist->setJustificationType (Justification::left);
  m_artist->setBounds (4, 40, 458, 22);
  addToLayout (m_artist, anchorTopLeft, anchorTopRight);
  addAndMakeVisible (m_artist);

  m_album = new Label;
  m_album->setFont (12);
  m_album->setColour (Label::textColourId, Colours::orange);
  m_album->setColour (Label::backgroundColourId, Colours::black.withAlpha (.1f));
  m_album->setJustificationType (Justification::left);
  m_album->setBounds (4, 66, 458, 20);
  addToLayout (m_album, anchorTopLeft, anchorTopRight);
  addAndMakeVisible (m_album);

  // Deck label

  {
    Label* c = new Label (String::empty, String::charToString ('A' + deckNumber));
    c->setFont (18);
    c->setColour (Label::textColourId, Colours::black);
    c->setColour (Label::backgroundColourId, Colours::yellow.darker ());
    c->setJustificationType (Justification::centred);
    c->setBounds (466, 4, 30, 30);
    addToLayout (c, anchorTopRight);
    addAndMakeVisible (c);
  }

  // Speed control

  m_speedControl = new CSpeedControl (m_deck->param["speed"]);
  m_speedControl->setBounds (466, 38, 30, 258);
  addToLayout (m_speedControl, anchorTopRight, anchorBottomRight);
  addAndMakeVisible (m_speedControl);

  {
    Label* c = new Label (String::empty, "Drop a music file.");
    c->setFont (24);
    c->setColour (Label::textColourId, Colours::white);
    c->setJustificationType (Justification::centred);
    c->setBounds (0, 100, 470, 160);
    addToLayout (c, anchorTopLeft, anchorBottomRight);
    addAndMakeVisible (c);

    m_text = c;
  }

  // Buttons

  {
    CParamToggleButton* c = new CParamToggleButton (
      "Play", m_deck->param ["play"]);
    c->setBounds (4, 276, 80, 20);
    addToLayout (c, anchorBottomLeft);
    addAndMakeVisible (c);
  }

  activateLayout ();

  m_deck->addListener (this, vf::MessageThread::getInstance());
}

CDeck::~CDeck()
{
  deleteAllChildren ();

  m_deck->removeListener (this);
}

void CDeck::paint (Graphics& g)
{
  Rectangle <int> r (getLocalBounds ());

  g.setColour (Colours::grey.brighter ());
  g.drawRect (r, 1);

  g.setColour (Colours::grey.darker ());
  g.fillRect (r);

}

void CDeck::paintOverChildren (Graphics& g)
{
  if (m_hasDropFocus)
  {
    Rectangle <int> r (getLocalBounds ());

    g.setColour (Colours::yellow.withAlpha (0.75f));
    g.drawRect (r, 16);
  }
}

bool CDeck::isInterestedInFileDrag (const StringArray& files)
{
  bool isInterested = false;

  if (files.size () == 1)
  {
    isInterested = FileManager::getInstance ().canHandleFile (files[0]);
  }

  return isInterested;
}

void CDeck::fileDragEnter (const StringArray& files, int x, int y)
{
  m_hasDropFocus = true;
  repaint ();
}

void CDeck::fileDragExit (const StringArray& files)
{
  m_hasDropFocus = false;
  repaint ();
}

void CDeck::filesDropped (const StringArray& files, int x, int y)
{
  if (m_hasDropFocus)
  {
    if (files.size () == 1)
    {
      String path = files [0];

      Playable::Ptr playable;
      
      playable = FileManager::getInstance ().createPlayableFromFile (path);

      if (playable != nullptr)
      {
        m_deck->selectPlayable (playable);

        m_text->setText (String::empty, false);
      }
      else
      {
        // display some sort of error message
      }
    }

    m_hasDropFocus = false;
    repaint ();
  }
}

void CDeck::onDeckSelect (Deck* deck, Playable::Ptr playable)
{
  if (playable != nullptr)
  {
    m_title->setText  (playable->getMetadata().title, true);
    m_artist->setText (playable->getMetadata().artist, true);
    m_album->setText  (playable->getMetadata().album, true);
  }
  else
  {
    m_title->setText  (String::empty, true);
    m_artist->setText (String::empty, true);
    m_album->setText  (String::empty, true);
  }
}

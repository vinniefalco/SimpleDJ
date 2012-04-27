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
#include "CMain.h"

CMain::CMain ()
  : vf::ResizableLayout (this)
{
  setSize (1024, 768);

  m_deck = new CDeck;
  m_deck->setBounds (0, 0, 1024, 768);
  addToLayout (m_deck, anchorTopLeft, anchorBottomRight);
  addAndMakeVisible (m_deck);

  activateLayout ();
}

CMain::~CMain()
{
}

void CMain::paint (Graphics& g)
{
  g.fillAll (Colours::black);

  Rectangle <int> r (getLocalBounds ());
  g.setFont (r.getHeight ()/3);
  g.setColour (Colours::white);
  g.drawText ("SimpleDJ", r.getX (), r.getY (), r.getWidth(), r.getHeight (),
    Justification::centred, true);
}

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

CMain::CMain (Mixer& mixer)
  : vf::ResizableLayout (this)
{
  setOpaque (true);
  setSize (1000, 700);

  Component* deck;
  
  deck = new CDeck (mixer);
  deck->setBounds (8, 8, 488, 288);
  addToLayout (deck, anchorTopLeft, Point <int> (50, 50));
  addAndMakeVisible (deck);

  deck = new CDeck (mixer);
  deck->setBounds (504, 8, 488, 288);
  addToLayout (deck, Point <int> (50, 0), Point <int> (100, 50));
  addAndMakeVisible (deck);

  deck = new CDeck (mixer);
  deck->setBounds (8, 304, 488, 288);
  addToLayout (deck, Point <int> (0, 50), Point <int> (50, 100));
  addAndMakeVisible (deck);

  deck = new CDeck (mixer);
  deck->setBounds (504, 304, 488, 288);
  addToLayout (deck, Point <int> (50, 50), anchorBottomRight);
  addAndMakeVisible (deck);

  activateLayout ();
}

CMain::~CMain()
{
  deleteAllChildren ();
}

void CMain::paint (Graphics& g)
{
  g.fillAll (Colours::black);
}

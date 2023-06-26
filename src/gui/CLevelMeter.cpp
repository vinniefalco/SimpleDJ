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
#include "CLevelMeter.h"

CLevelMeter::CLevelMeter ()
{
  m_level.peak = 0;
  m_level.clip = false;
}

CLevelMeter::~CLevelMeter ()
{
}

void CLevelMeter::paint (Graphics& g)
{
  juce::Rectangle <int> r = getLocalBounds ();

  g.setColour (Colours::white);
  g.drawRect (r);
  r = r.reduced (1, 1);

  g.setColour (Colours::black);

  float const peak = std::min (m_level.peak, 1.0f);

  if (r.getWidth () > r.getHeight ())
  {
    // horizontal
    r.setWidth (int (r.getWidth () * peak + 0.5));
  }
  else
  {
    // vertical
    r.setTop (int (r.getBottom () - (r.getHeight () * peak + 0.5)));
  }

  if (m_level.peak < 0.7f)
    g.setColour (Colours::green);
  else if (m_level.peak < 1.0f)
    g.setColour (Colours::orange);
  else
    g.setColour (Colours::red);
  g.fillRect (r);
}

void CLevelMeter::setLevel (Mixer::Level level)
{
  m_level = level;

  repaint ();
}

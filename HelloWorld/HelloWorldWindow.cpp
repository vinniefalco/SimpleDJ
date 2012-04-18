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

#include "JuceHeader.h"
#include "HelloWorldWindow.h"
#include "HelloWorldComponent.h"

HelloWorldWindow::HelloWorldWindow() : DocumentWindow (
  JUCEApplication::getInstance()->getApplicationName(),
  Colour(0xff333333),
  DocumentWindow::allButtons,
  true)
{
  setSize (640, 480);
  setContentOwned (new HelloWorldComponent, true);

  centreWithSize (800, 500);
  setResizable (true, false);
}

HelloWorldWindow::~HelloWorldWindow()
{
}

void HelloWorldWindow::closeButtonPressed ()
{
  JUCEApplication::getInstance()->systemRequestedQuit();
}

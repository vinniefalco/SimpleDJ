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
#include "Param.h"

Param::Param (String name,
              double initialValue,
              vf::CallQueue& owningThread)
  : m_name (name)
  , m_state (initialValue)
  , m_thread (owningThread)
{
}

String Param::getName () const
{
  return m_name;
}

void Param::addListener (Listener* listener, vf::CallQueue& thread)
{
  // This is asking for trouble.
  jassert (&thread != &m_thread);

  // Atomically add the listener and synchronize their state.

  StateType::ReadAccess state (m_state);

  m_listeners.add (listener, thread);

  m_listeners.queue1 (listener, &Listener::onParamChange, this, state->value);
}

void Param::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void Param::setValue (double value)
{
  // Are we being called by the owning thread?
  if (m_thread.isAssociatedWithCurrentThread ())
  {
    // Set the value directly
    doSetValue (value);
  }
  else
  {
    // Change the value from the owning thread.
    m_thread.call (&Param::doSetValue, this, value);
  }
}

void Param::doSetValue (double value)
{
  // Atomically change state and notify listeners.

  StateType::WriteAccess state (m_state);

  state->value = value;

  m_listeners.queue (&Listener::onParamChange, this, value);
}

double Param::doGetValue () const
{
  // This should only be called from the owning thread!
  jassert (m_thread.isAssociatedWithCurrentThread ());

  return StateType::UnlockedAccess (m_state)->value;
}

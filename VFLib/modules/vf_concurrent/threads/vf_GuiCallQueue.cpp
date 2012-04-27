/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

namespace
{

// This tries to solve the problem where continual streams of work
// cause some painting not to occur. This bug was fixed in JUCE.
//
void updateAllTopLevelWindows ()
{
#if JUCE_WINDOWS
  // This screws up
  static bool inUpdate = false;

  if (!inUpdate)
  {
    inUpdate = true;

    int n = juce::TopLevelWindow::getNumTopLevelWindows();
    for (int i = 0; i < n; ++i)
    {
      juce::TopLevelWindow* w = juce::TopLevelWindow::getTopLevelWindow (i);
      juce::ComponentPeer* peer = w->getPeer ();
      if (peer)
        peer->performAnyPendingRepaintsNow ();
    }

    inUpdate = false;
  }
#endif
}

}

GuiCallQueue::GuiCallQueue () : CallQueue ("GuiCallQueue")
{
  // This object must be created from the Juce Message Thread.
  //
  vfassert (juce::MessageManager::getInstance()->isThisTheMessageThread());

  // Associate the CallQueue with the message thread right away.
  //
  synchronize ();
}

void GuiCallQueue::close ()
{
  CallQueue::close ();
}

bool GuiCallQueue::synchronize ()
{
  return CallQueue::synchronize ();
}

void GuiCallQueue::signal ()
{
  triggerAsyncUpdate ();
}

void GuiCallQueue::reset ()
{
}

void GuiCallQueue::handleAsyncUpdate()
{
  synchronize ();

  //updateAllTopLevelWindows ();
}

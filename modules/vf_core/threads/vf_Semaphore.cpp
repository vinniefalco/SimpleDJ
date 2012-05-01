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

Semaphore::Semaphore (int initialCount)
  : m_counter (initialCount)
{
}

Semaphore::~Semaphore ()
{
  // Can't delete the semaphore while threads are waiting on it!!
  jassert (m_waitingThreads.pop_front () == nullptr);

  for (;;)
  {
    WaitingThread* waitingThread = m_deletedList.pop_front ();

    if (waitingThread != nullptr)
      delete waitingThread;
  }
}

void Semaphore::signal (int amount)
{
  jassert (amount > 0);

  while (amount--)
  {
    // Increment and release a waiting thread if the count is positive.
    if (++m_counter > 0)
    {
      WaitingThread* waitingThread = m_waitingThreads.pop_front ();

      if (waitingThread != nullptr)
        waitingThread->m_event.signal ();
    }
  }
}

void Semaphore::wait ()
{
  // Decrement the count and wait if needed.
  if (--m_counter < 0)
  {
    // Try to recycle an element from the deleted list.
    WaitingThread* waitingThread = m_deletedList.pop_front ();

    if (waitingThread == nullptr)
    {
      // Nothing to recycle so make a new one.
      waitingThread = new WaitingThread;
    }

    // Put us on the waiting list.
    m_waitingThreads.push_front (waitingThread);

    // Wait until a resource is available.
    waitingThread->m_event.wait ();

    // We've been taken off the waiting list so put this
    // element on the deleted list to get recycled.
    m_deletedList.push_front (waitingThread);
  }
}

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
  for (List <WaitingThread>::iterator iter = m_deletedList.begin ();
       iter != m_deletedList.end ();)
  {
    delete &(*iter++);
  }
}

void Semaphore::signal (int amount)
{
  jassert (amount > 0);

  ScopedLock lock (m_mutex);

  m_counter += amount;

  if (m_counter >= 0)
  {
    if (!m_waitingThreads.empty ())
    {
      WaitingThread* w = &m_waitingThreads.front ();

      m_waitingThreads.pop_front ();

      w->m_event.signal ();
      w->m_signaled = true;
    }
  }
}

bool Semaphore::wait (int timeoutMilliseconds)
{
  bool isSignaled = false;
  WaitingThread* w = nullptr;

  {
    ScopedLock lock (m_mutex);

    if (--m_counter < 0)
    {
      if (m_deletedList.size () > 0)
      {
        w = &m_deletedList.front ();
        
        m_deletedList.pop_front ();
      }
      else
      {
        w = new WaitingThread;
      }

      m_waitingThreads.push_front (*w);
    }
  }

  if (w != nullptr)
  {
    w->m_event.wait (timeoutMilliseconds);

    {
      ScopedLock lock (m_mutex);

      isSignaled = w->m_signaled;

      m_waitingThreads.erase (w);
    }

    m_deletedList.push_front (*w);
  }

  return isSignaled;
}

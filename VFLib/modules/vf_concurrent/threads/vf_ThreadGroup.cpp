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

ThreadGroup::Worker::Worker (String name) : Thread (name)
{
  startThread ();
}

ThreadGroup::Worker::~Worker ()
{
  stopThread (-1);
}

void ThreadGroup::Worker::queue (Work* work)
{
  bool const becameSignaled = m_queue.push_back (work);

  if (becameSignaled)
    notify ();
}

void ThreadGroup::Worker::run ()
{
  while (!threadShouldExit ())
  {
    wait (-1);

    Work* w;

    do
    {
      w = m_queue.pop_front ();

      if (w)
      {
        w->operator() ();

        delete w;
      }
    }
    while (w);
  }
}

//==============================================================================

ThreadGroup::ThreadGroup ()
{
  setNumberOfThreads (SystemStats::getNumCpus ());
}

ThreadGroup::ThreadGroup (int numberOfThreads)
{
  setNumberOfThreads (numberOfThreads);
}

ThreadGroup::~ThreadGroup ()
{
  setNumberOfThreads (0);
}

void ThreadGroup::setNumberOfThreads (int numberOfThreads)
{
  jassert (numberOfThreads >= 0);

  LockType::ScopedLockType lock (m_mutex);

  int previousSize = m_threads.size ();

  if (numberOfThreads > previousSize)
  {
    do
    {
      String s;
      s << "ThreadGroup (" << (m_threads.size () + 1) << ")";

      Worker* worker = new Worker (s);

      m_threads.push_back (*worker);
    }
    while (m_threads.size () < numberOfThreads);
  }
  else
  {
    while (numberOfThreads < m_threads.size ())
    {
      Worker* worker = &m_threads.front ();

      m_threads.erase (worker);

      delete worker;
    }
  }
}

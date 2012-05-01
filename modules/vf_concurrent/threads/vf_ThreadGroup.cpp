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

ThreadGroup::Worker::Worker (String name, ThreadGroup& group)
  : Thread (name)
  , m_group (group)
{
  startThread ();
}

ThreadGroup::Worker::~Worker ()
{
  // Make sure the thread is stopped
  stopThread (-1);

  // Remove ourselves from the list.
  m_group.m_threads.erase (this);
}

void ThreadGroup::Worker::run ()
{
  do
  {
    m_group.m_semaphore.wait ();

    Work* work = m_group.m_queue.pop_front ();

    jassert (work != nullptr);

    work->operator() (this);

    delete work;
  }
  while (!threadShouldExit ());
}

//==============================================================================

void ThreadGroup::QuitType::operator() (Worker* worker)
{
  worker->signalThreadShouldExit ();
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
  while (!m_threads.empty ())
    killOneWorker ();
}

void ThreadGroup::setNumberOfThreads (int numberOfThreads)
{
  jassert (numberOfThreads > 0);

  int previousSize = m_threads.size ();

  if (numberOfThreads > previousSize)
  {
    do
    {
      String s;
      s << "ThreadGroup (" << (m_threads.size () + 1) << ")";

      Worker* worker = new Worker (s, *this);

      m_threads.push_back (*worker);
    }
    while (m_threads.size () < numberOfThreads);
  }
  else
  {
    while (numberOfThreads < m_threads.size ())
      killOneWorker ();
  }
}

void ThreadGroup::killOneWorker ()
{
  m_queue.push_front (new (getAllocator ()) QuitType);
}

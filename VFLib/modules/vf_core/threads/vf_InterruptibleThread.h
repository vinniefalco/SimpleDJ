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

#ifndef VF_INTERRUPTIBLETHREAD_VFHEADER
#define VF_INTERRUPTIBLETHREAD_VFHEADER

#include "../diagnostic/vf_SafeBool.h"
#include "../functor/vf_Function.h"

/*============================================================================*/
/**
  A thread with soft interruption support.

  The thread must periodically call interruptionPoint(), which returns
  true the first time an interruption has occurred since the last call to
  interruptionPoint().

  @ingroup vf_core
*/
class InterruptibleThread : public juce::Thread
{
public:
  // This is the flag used to indicate if an interruption
  // occurred when using the polling model. It is designed
  // to detect improper usage (specifically, not checking
  // the flag, which would result in incorrect behavior).
  //
  // #1 The default constructor must produce an object that
  //    is considered non-signaled (i.e. not interrupted)
  //    in order for ThreadWithCallQueue that uses a default Callable
  //    for its idle function to work.
  //
  class Interrupted : public SafeBool <Interrupted>
  {
  public:
    Interrupted ()
     : m_interrupted (false)
     , m_checked (false)
    {
    }

    explicit Interrupted (bool interrupted)
     : m_interrupted (interrupted)
     , m_checked (false)
    {
    }

    Interrupted (const Interrupted& other)
      : m_interrupted (other.m_interrupted)
      , m_checked (false)
    {
      other.m_checked = true;
    }

    ~Interrupted ()
    {
      vfassert (!m_interrupted || m_checked);
    }

    Interrupted& operator= (const Interrupted& other)
    {
      m_interrupted = other.m_interrupted;
      m_checked = false;
      other.m_checked = true;
      return *this;
    }

    bool asBoolean () const
    {
      m_checked = true;
      return m_interrupted;
    }

  private:
    bool m_interrupted;
    bool mutable m_checked;
  };

  typedef juce::Thread::ThreadID id;

public:
  explicit InterruptibleThread (String name);
  ~InterruptibleThread ();

  void start (Function <void (void)> const& f);

  void join ();

  // Blocks until an interrupt occurs or the timeout expires.
  // If milliseconds is less than 0, the wait is infinite.
  // May only be called by the thread of execution.
  // Returns true if the interrupt occurred, or false if
  // the timeout expired.
  //
  bool wait (int milliSeconds = -1);

  // Interrupts the thread.
  //
  void interrupt ();

  // Called by the thread function, returns an Interrupted
  // object indicating whether or not interruption is requested.
  //
  Interrupted interruptionPoint ();

  id getId () const;

  // Returns true if the caller is this thread of execution.
  // Only valid if the thread has been started.
  //
  bool isTheCurrentThread () const;

  // Adjusts the priority, range is 0...10.
  // Only available in some implementations.
  //
  void setPriority (int priority);

private:
  void run ();

  Function <void (void)> m_function;
  juce::WaitableEvent m_runEvent;
  id m_threadId;

  enum
  {
    stateRun,
    stateInterrupt,
    stateReturn,
    stateWait
  };

  AtomicState m_state;
};

//------------------------------------------------------------------------------

namespace CurrentInterruptibleThread
{

extern InterruptibleThread::Interrupted interruptionPoint ();

}

#endif

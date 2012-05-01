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

#ifndef VF_THREADGROUP_VFHEADER
#define VF_THREADGROUP_VFHEADER

#include "../memory/vf_AllocatedBy.h"
#include "../memory/vf_FifoFreeStore.h"

#include "vf_CallQueue.h"

/*============================================================================*/
/**
  @ingroup vf_concurrent

  @brief A group of threads for performing asynchronous tasks.

  @see ParallelFor
*/
class ThreadGroup
{
public:
  typedef FifoFreeStoreType AllocatorType;

  /** Creates one thread per CPU.
  */
  ThreadGroup ();

  /** Creates the specified number of threads.
  */
  explicit ThreadGroup (int numberOfThreads);

  ~ThreadGroup ();

  /** Returns the number of threads.
  */
  int getNumberOfThreads () const
  {
    return m_threads.size ();
  }

  /** Sets the number of concurrent threads.
      If the number of threads is reduced, excess threads will
      complete their calls before destroying themselves.
  */
  void setNumberOfThreads (int numberOfThreads);

  /** Calls a functor on all threads simultaneously.
  */
  template <class Functor>
  void callf (Functor const& f)
  {
    LockType::ScopedLockType lock (m_mutex);

    if (m_threads.size () > 0)
    {
      for (List <Worker>::iterator iter = m_threads.begin ();
           iter != m_threads.end (); ++iter)
        iter->queue (new (m_allocator) WorkType <Functor> (f));
    }
  }

  /** Allocator access.
  */
  inline AllocatorType& getAllocator ()
  {
    return m_allocator;
  }

  template <class Fn>
  void call (Fn f)
  { callf (vf::bind (f)); }

  template <class Fn, typename  T1>
  void call (Fn f,    const T1& t1)
  { callf (vf::bind (f, t1)); }

  template <class Fn, typename  T1, typename  T2>
  void call (Fn f,    const T1& t1, const T2& t2)
  { callf (vf::bind (f, t1, t2)); }

  template <class Fn, typename  T1, typename  T2, typename  T3>
  void call (Fn f,    const T1& t1, const T2& t2, const T3& t3)
  { callf (vf::bind (f, t1, t2, t3)); }

  template <class Fn, typename  T1, typename  T2,
                      typename  T3, typename  T4>
  void call (Fn f,    const T1& t1, const T2& t2,
                      const T3& t3, const T4& t4)
  { callf (vf::bind (f, t1, t2, t3, t4)); }

  template <class Fn, typename  T1, typename  T2, typename  T3,
                      typename  T4, typename  T5>
  void call (Fn f,    const T1& t1, const T2& t2, const T3& t3,
                      const T4& t4, const T5& t5)
  { callf (vf::bind (f, t1, t2, t3, t4, t5)); }

  template <class Fn, typename  T1, typename  T2, typename  T3,
                      typename  T4, typename  T5, typename  T6>
  void call (Fn f,    const T1& t1, const T2& t2, const T3& t3,
                      const T4& t4, const T5& t5, const T6& t6)
  { callf (vf::bind (f, t1, t2, t3, t4, t5, t6)); }

  template <class Fn, typename  T1, typename  T2, typename  T3, typename  T4,
                      typename  T5, typename  T6, typename  T7>
  void call (Fn f,    const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                      const T5& t5, const T6& t6, const T7& t7)
  { callf (vf::bind (f, t1, t2, t3, t4, t5, t6, t7)); }

  template <class Fn, typename  T1, typename  T2, typename  T3, typename  T4,
                      typename  T5, typename  T6, typename  T7, typename  T8>
  void call (Fn f,    const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                      const T5& t5, const T6& t6, const T7& t7, const T8& t8)
  { callf (vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8)); }

  //============================================================================
private:
  class Work : public LockFreeQueue <Work>::Node,
               public AllocatedBy <AllocatorType>
  {
  public:
    virtual ~Work () { }
    virtual void operator() () = 0;
  };

  template <class Functor>
  class WorkType : public Work
  {
  public:
    explicit WorkType (Functor const& f) : m_f (f) { }
    ~WorkType () { }
    void operator() () { m_f (); }

  private:
    Functor m_f;
  };

private:
  class Worker
    : public List <Worker>::Node
    , public Thread
  {
  public:
    explicit Worker (String name);
    ~Worker ();

    void queue (Work* work);

  private:
    void run ();

  private:
    LockFreeQueue <Work> m_queue;
  };

  typedef SpinLock LockType;
  
  AllocatorType m_allocator;
  List <Worker> m_threads;
  LockType m_mutex;
};

#endif

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

  @brief A group of threads for parallelizing tasks.

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

      @param numberOfThreads The number of threads in the group. This must be
                             greater than zero.
  */
  explicit ThreadGroup (int numberOfThreads);

  ~ThreadGroup ();

  /** Determine the number of threads in the group.

      @return The number of threads in the group.
  */
  int getNumberOfThreads () const
  {
    return m_threads.size ();
  }

  /** Sets the number of concurrent threads.

      If the number of threads is reduced, excess threads will complete
      their work before being destroyed.

      @note This is not thread safe with call().

      @param numberOfThreads The number of threads in the group. This must be
                             greater than zero.
  */
  void setNumberOfThreads (int numberOfThreads);

  /** Calls a functor on multiple threads.

      The specified functor is executed on some or all available threads at once.
      A call is always guaranteed to execute.

      @param maxThreads The maximum number of threads to use, or -1 for all.
  */
  template <class Functor>
  void callf (int maxThreads, Functor const& f)
  {
    jassert (maxThreads > 0 || maxThreads == -1);

    int numberOfThreads = getNumberOfThreads ();

    if (maxThreads != -1 && maxThreads < numberOfThreads)
      numberOfThreads = maxThreads;

    while (numberOfThreads--)
    {
      m_queue.push_front (new (getAllocator ()) WorkType <Functor> (f));
      m_semaphore.signal ();
    }
  }

  /** Allocator access.
  */
  inline AllocatorType& getAllocator ()
  {
    return m_allocator;
  }

  template <class Fn>
  void call (int maxThreads, Fn f)
  { callf (maxThreads, vf::bind (f)); }

  template <class Fn,              typename  T1>
  void call (int maxThreads, Fn f, const T1& t1)
  { callf (maxThreads, vf::bind (f, t1)); }

  template <class Fn,              typename  T1, typename  T2>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2)
  { callf (maxThreads, vf::bind (f, t1, t2)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3)
  { callf (maxThreads, vf::bind (f, t1, t2, t3)); }

  template <class Fn,              typename  T1, typename  T2,
                                   typename  T3, typename  T4>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2,
                                   const T3& t3, const T4& t4)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3,
                                   typename  T4, typename  T5>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3,
                                   const T4& t4, const T5& t5)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3,
                                   typename  T4, typename  T5, typename  T6>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3,
                                   const T4& t4, const T5& t5, const T6& t6)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3, typename  T4,
                                   typename  T5, typename  T6, typename  T7>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                                   const T5& t5, const T6& t6, const T7& t7)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6, t7)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3, typename  T4,
                                   typename  T5, typename  T6, typename  T7, typename  T8>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                                   const T5& t5, const T6& t6, const T7& t7, const T8& t8)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8)); }

private:
  void killOneWorker ();

  //============================================================================
private:
  /** A thread in the group.
  */
  class Worker
    : public List <Worker>::Node
    , public Thread
  {
  public:
    Worker (String name,
            ThreadGroup& group);

    ~Worker ();

  private:
    void run ();

  private:
    ThreadGroup& m_group;
  };

  //============================================================================
private:
  /** Abstract work item.
  */
  class Work : public LockFreeStack <Work>::Node,
               public AllocatedBy <AllocatorType>
  {
  public:
    virtual ~Work () { }

    /* The worker is passed in so we can make it quit later.
    */
    virtual void operator() (Worker* worker) = 0;
  };

  template <class Functor>
  class WorkType : public Work
  {
  public:
    explicit WorkType (Functor const& f) : m_f (f) { }
    ~WorkType () { }
    void operator() (Worker*) { m_f (); }

  private:
    Functor m_f;
  };

  /** Used to make a Worker stop
  */
  class QuitType : public Work
  {
  public:
    void operator() (Worker* worker);
  };

private:
  Semaphore m_semaphore;
  AllocatorType m_allocator;
  List <Worker> m_threads;
  LockFreeStack <Work> m_queue;
};

#endif

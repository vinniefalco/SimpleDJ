// thread queue for callback functor..

#include "../JuceLibraryCode/JuceHeader.h"
#include "ThreadQueue.h"

ThreadQueue::ThreadQueue () : isClosed (false), headNode (0), tailNode (0)
{
}

ThreadQueue::~ThreadQueue ()
{
    jassert (isClosed)

    jassert (headNode == nullptr && tailNode == nullptr)
}

//====================================================
// interface and core function...  

// 1. lock() and unlock() CriticalSection object.
// 2. iterating the queue, handling each node (functor).
// 3. all of nodes (functor) leave queue.

void ThreadQueue::process ()
{
    Node* headPtr;
    lock ();

    headPtr = headNode;
    headNode = nullptr;
    tailNode = nullptr;

    if (headPtr != nullptr)
        reset();

    unlock ();

    if (headPtr != nullptr)
    {
        // iterating queue, handling each functor...
        for (Node* curFct = headPtr; curFct != nullptr; curFct = curFct->nextNode)
            curFct->operator ()();

        // all of nodes leave queue...
        for (Node* curFct = headPtr; curFct != nullptr; )
        {
            Node* temp = curFct->nextNode;
            delete curFct;
            curFct = temp;
        }
    }
}

//====================================================
void ThreadQueue::lock ()
{
    mutex.enter();
}

void ThreadQueue::unlock ()
{
    mutex.exit();
}

// =======================================

// put functor to queue...
void ThreadQueue::put (Node* node)
{
    lock ();

    jassert (!isClosed)

    bool shouldSignal = (nullptr == headNode);
    
    // add to the queue...
    node->nextNode = nullptr;
    node->prevNode = tailNode;

    if (node->prevNode != nullptr)
        node->prevNode->nextNode = node;
    else
        headNode = node;

    tailNode = node;

    if (shouldSignal)
        signal ();

    unlock();
}

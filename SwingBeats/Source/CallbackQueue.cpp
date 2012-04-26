/*
====================================================================================
            Swing Beats

    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    License: MIT License, Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CallbackQueue.h"

//==================================================================================
CallbackQueue::CallbackQueue () : isClosed (false), headNode (0), tailNode (0)
{
}

//==================================================================================
CallbackQueue::~CallbackQueue ()
{
    jassert (isClosed)

    jassert (headNode == nullptr && tailNode == nullptr)
}

//==================================================================================
/* interface and core function...  

 1) lock() and unlock() CriticalSection object.
 2) iterating the queue, handling each node (functor).
 3) all of nodes (functor) leave queue.
*/
void CallbackQueue::process ()
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

//==================================================================================
void CallbackQueue::lock ()
{
    mutex.enter();
}

//==================================================================================
void CallbackQueue::unlock ()
{
    mutex.exit();
}

//==================================================================================
// put functor to queue...
void CallbackQueue::put (Node* node)
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

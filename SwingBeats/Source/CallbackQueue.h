// thread queue for callback functor..

#ifndef _THREADQUEUE_H
#define _THREADQUEUE_H

class ThreadQueue
{
public:
    //============================================
    ThreadQueue ();
    ~ThreadQueue ();

    void process ();

    void open () { isClosed = false; }
    void close () { isClosed = true; }    

    // interface function, inline...
    template<class Functor>
    void call (const Functor& functor)
    {
        // put functor to queue..
        put (new FunctorNode<Functor> (functor));
    }

private:
    //==============================================
    // nested class 1, ADT
    class Node
    {
    public:
        virtual ~Node() { }        
        virtual void operator()() = 0;
        
        Node* nextNode;
        Node* prevNode;
    };  
    //===============================================
    // nested class 2 inherits class 1, class template.
    template<class T>
    class FunctorNode : public Node
    {
    public:
        explicit FunctorNode (const T& func) : functor (func)  { }
        FunctorNode& operator= (const FunctorNode& other) { functor = other.functor; }
        void operator()() { functor.operator()(); }

    private:
        T functor;
    }; 
    
    //===============================================
    void put (Node* functorNode);

    void lock ();
    void unlock ();

    virtual void signal () = 0;
    virtual void reset () = 0;

    //===============================================
    CriticalSection mutex;

    bool isClosed;

    Node* headNode;
    Node* tailNode;
};

#endif  // _THREADQUEUE_H_

#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"

class QueueEmptyException : public RuntimeException
{
public:
    QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

// A linked list node using to store a queue entry
template<typename Object>
struct Node
{
    Object data;
    Node* next;
};


template<typename Object>
class LLQueue
{
private:
    // fill in private member data here
    Node<Object>* head; // head pointer points to the head of queue
    Node<Object>* rear; // rear pointer points to the rear of queue
    size_t sz;          // count current size of queue

public:
    LLQueue();
//  In principle, you should have copy constructors and 
// assignment operators implemented.
// I am not going to require it for this assignment.
//    LLQueue(const LLQueue & st);
//  LLQueue & operator=(const LLQueue & st);
    ~LLQueue()
    {
        while (head != nullptr)
        {
            Node<Object>* n = head;
            head = head->next;
            delete n;
        }
    }

    size_t size() const noexcept;
    bool isEmpty() const noexcept;

    // We have two front() for the same reason the Stack in lecture week 2 had two top() functions.
    // If you do not know why there are two, your FIRST step needs to be to review your notes from that lecture.

    Object & front();
    const Object & front() const;

    void enqueue(const Object & elem);
// does not return anything.  Just removes. 
    void dequeue();
};

// TODO:  Fill in the functions here. 
template<typename Object>
LLQueue<Object>::LLQueue()
    : head{nullptr}, rear{nullptr}, sz{0}
{
}

template<typename Object>
size_t LLQueue<Object>::size() const noexcept
{
    return sz;
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept
{
    if (sz == 0) { return true; }
    return false;
}

template<typename Object>
Object& LLQueue<Object>::front()
{
    if (isEmpty())
    {
        throw QueueEmptyException("Access to empty queue");
    }
    return head->data;
}

template<typename Object>
const Object& LLQueue<Object>::front() const
{
    if (isEmpty())
    {
        throw QueueEmptyException("Access to empty queue");
    }
    return head->data;
}

template<typename Object>
void LLQueue<Object>::enqueue(const Object& elem)
{
    Node<Object>* n = new Node<Object>{elem, nullptr};
    if (isEmpty())
    {
        head = rear = n;
    }
    else
    {
        rear->next = n;
        rear = rear->next;
    }
    sz++;
}

template<typename Object>
void LLQueue<Object>::dequeue()
{
    if (isEmpty())
    {
        throw QueueEmptyException("Dequeued from empty queue");
    }
    if (sz == 1)
    {
        delete head;
        head = rear = nullptr;
    }
    else
    {
        Node<Object>* n = head->next;
        delete head;
        head = n;
    }
    sz--;
}



#endif

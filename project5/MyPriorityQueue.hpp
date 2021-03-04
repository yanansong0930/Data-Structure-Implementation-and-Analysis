#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>
#include <algorithm>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
	std::vector<Object> min_heap;
    int sz;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:

	// You also need a constructor and a destructor.
    MyPriorityQueue();
    
 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
    min_heap.push_back(Object());
    sz = 0;
}


template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return sz;
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return (sz==0);
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
    sz++;
	min_heap.push_back(elem);
    heapifyUp(sz);
}

template<typename Object>
void MyPriorityQueue<Object>::heapifyUp(int index)
{
    // check if node at index and its parent
    // violate the min heap property
    if (index > 1)
    {
        int parent = index / 2;
        if (min_heap.at(index) < min_heap.at(parent))
        {
            std::swap(min_heap.at(parent),min_heap.at(index));  
            // recusively call this function
            heapifyUp(parent);
        }
    }
}


template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
    if (isEmpty())
    {
        throw PriorityQueueEmptyException("Priority Queue is Empty");
    }
	return min_heap.at(1); 
}



template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
    if (isEmpty())
    {
        throw PriorityQueueEmptyException("Priority Queue is Empty");
    }
    min_heap.at(1) = min_heap.at(sz);
    min_heap.pop_back();
    sz--;
    heapifyDown(1);
}

template<typename Object>
void MyPriorityQueue<Object>::heapifyDown(int index)
{
    // re-arrange the heap from top to bottom so that
    // after completion it doesn't violate min heap property
    int left = 2 * index;
    int right = 2 * index + 1;
    
    if (left < (sz+1) && right < (sz+1))
    {
        int small;
        if (min_heap.at(left) < min_heap.at(right))
        {
            small = left;
        }
        else { small = right; }

        if (min_heap[small] < min_heap[index])
        {
            std::swap(min_heap[small], min_heap[index]);
            heapifyDown(small);
        }
    }
    
}
#endif

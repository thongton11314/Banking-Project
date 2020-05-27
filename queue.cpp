#include "queue.h"

// constructor
// initialize queue
Queue::Queue() {

    // front is rear at the begining
    front = rear = nullptr;
}

// deconstructor
// deallocate memory
Queue::~Queue() {
    clear();
}

// clear
// delete each node carefully since allocate them
void Queue::clear() {

    // keep deleting if queue still has datas
    while (front != nullptr) {

        // using for next node
        Node* temp = front;
        front = front->next;

        // delete node
        delete temp->data;
        delete temp;
        temp = nullptr;
    }

    // always set null pointer when done
    front = rear = nullptr;
}

bool Queue::isEmpty() const {
    return (front == nullptr);
}

// enqueue
// insert item into rear of queue
bool Queue::enqueue(Transaction * dataptr) {

    Node* nodeptr = new Node;
    assert(nodeptr != nullptr);
    nodeptr->data = dataptr;
    nodeptr->next = nullptr;

    // link at front if empty, otherwise at the rear
    if (isEmpty())
        front = nodeptr;
    else
        rear->next = nodeptr;
    rear = nodeptr;                                // either way, rear is set
    return true;
}

// dequeue
// remove item from front of queue
bool Queue::dequeue(Transaction *& dataptr) {
    if (isEmpty())
        return false;

    dataptr = front->data;
    Node* nodeptr = front;
    front = front->next;
    if (isEmpty())
        rear = nullptr;                   // if it's the last node in queue
    delete nodeptr;
    nodeptr = nullptr;
    return true;
}

// peak
// retrieve item at front of queue
bool Queue::peek(Transaction *& dataptr) const {
    if (isEmpty())
        return false;

    dataptr = front->data;
    return true;
}
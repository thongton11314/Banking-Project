#include "queue.h"

//----------------------------------------------------------------------------
// constructor
// initialize queue
Queue::Queue() {

    // front is rear at the begining
    front = rear = nullptr;
}

//----------------------------------------------------------------------------
// deconstructor
// deallocate memory
Queue::~Queue() {
    clear();
}

//----------------------------------------------------------------------------
// clear
// delete every node
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

//----------------------------------------------------------------------------
// isEmpty
// check queue empty
bool Queue::isEmpty() const {
    return (front == nullptr);
}

//----------------------------------------------------------------------------
// enqueue
// insert new item into the rear of queue
bool Queue::enqueue(Transaction * dataptr) {

    Node* nodeptr = new Node;   // create new node
    assert(nodeptr != nullptr); // out of memory
    nodeptr->data = dataptr;
    nodeptr->next = nullptr;

    // link at front if empty, otherwise at the rear
    if (isEmpty())
        front = nodeptr;
    else
        rear->next = nodeptr;
    rear = nodeptr;                            // either way, rear is set
    return true;
}

//----------------------------------------------------------------------------
// dequeue
// remove item from front of queue
// the parameter will take the dequeued data
// return true if dequeue successfully
//        false if queue is empty
bool Queue::dequeue(Transaction *& dataptr) {
    
    // early exit, if no transaction
    if (isEmpty())
        return false;

    // assign first node's data to dataptr then delete it in queue
    dataptr = front->data;
    Node* nodeptr = front;
    front = front->next;
    if (isEmpty())
        rear = nullptr;                   // if it's the last node in queue
    delete nodeptr;
    nodeptr = nullptr;
    return true;
}

//----------------------------------------------------------------------------
// peak
// retrieve item at the front of queue
// the parameter will point to the first data in queue
bool Queue::peek(Transaction *& dataptr) const {
    
    //  empty
    if (isEmpty())
        return false;

    // not empty
    dataptr = front->data;
    return true;
}

// operator<<
// output operator for class queue, print data, 
// responsibility for output object stored in the queue
ostream & operator<<(ostream & output, const Queue & obj) {
    Queue::Node* current = obj.front;
        while (current != nullptr) {
            output << *current->data << endl;
            current = current->next;
        }
        return output;
}

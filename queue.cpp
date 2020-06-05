#include "queue.h"

Queue::Queue() {
    front = rear = nullptr;
}

Queue::~Queue() {
    clear();
}

void Queue::clear() {


    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp->data;
        delete temp;
        temp = nullptr;
    }
    front = rear = nullptr;
}

bool Queue::isEmpty() const {
    return (front == nullptr);
}

bool Queue::enqueue(Transaction * dataptr) {

    Node* nodeptr = new Node;
    assert(nodeptr != nullptr);
    nodeptr->data = dataptr;
    nodeptr->next = nullptr;
    if (isEmpty())
        front = nodeptr;
    else
        rear->next = nodeptr;
    rear = nodeptr;  
    return true;
}

bool Queue::dequeue(Transaction *& dataptr) {
    if (isEmpty())
        return false;

    dataptr = front->data;
    Node* nodeptr = front;
    front = front->next;
    if (isEmpty())
        rear = nullptr;       
    delete nodeptr;
    nodeptr = nullptr;
    return true;
}

bool Queue::peek(Transaction *& dataptr) const {
    if (isEmpty())
        return false;

    dataptr = front->data;
    return true;
}

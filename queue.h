#pragma once
#ifndef HISTORY_AND_TRANSACTION_CONTAINER
#define HISTORY_AND_TRANSACTION_CONTAINER
#include <ostream>
#include "transaction.h"

// Asumption?
// What ADT use ? queue

using namespace std;

class Queue {
    friend ostream &operator<<(ostream&, const Queue&);

public:
    Queue();                        // default constructor
    ~Queue();                       // destructor
    Queue(const Queue&);            // copy constructor
    void clear();                   // clear out queue
    bool isEmpty() const;           // is the queue empty?

    // insert item, assume object passed in is valid, return whether successful
    bool enqueue(Transaction*);

    // remove item, parameter is removed item, return whether item is removed 
    bool dequeue(Transaction*&);

    // retrieve item, parameter is item at top, return whether item exists
    bool peek(Transaction*&) const;

private:
    struct Node {
        Transaction* data;          // pointer to actual data stored
        Node* next;
    };

    // for linked list implementation
    Node* front;                    // pointer to front of queue
    Node* rear;                     // pointer to rear of queue
};
#endif // !HISTORY_AND_TRANSACTION_CONTAINER


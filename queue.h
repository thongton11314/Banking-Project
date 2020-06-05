#pragma once
#ifndef HISTORY_AND_TRANSACTION_CONTAINER
#define HISTORY_AND_TRANSACTION_CONTAINER
#include <ostream>
#include <assert.h>
#include "transaction.h"

// Asumption?
// What ADT use ? queue

using namespace std;

class Queue {

    // g++ has problems with friend template functions and class templates
    // so put the code for operator<< here, in the class definition
    // output operator for class queue, print data, 
    // responsibility for output is left to object stored in the queue
    friend ostream &operator<<(ostream & output, const Queue & obj) {
        Queue::Node* current = obj.front;
        while (current != nullptr) {
            output << *current->data << endl;
            current = current->next;
        }
        return output;
    }

public:
    Queue();                        // default constructor
    ~Queue();                       // destructor
    void clear();                   // clear out queue
    bool isEmpty() const;           // is the queue empty?
    bool enqueue(Transaction*);
    bool dequeue(Transaction*&);
    bool peek(Transaction*&) const;
private:
    struct Node {
        Transaction* data;
        Node* next;
    };
    Node* front;
    Node* rear;
};
#endif

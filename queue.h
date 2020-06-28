#pragma once
#ifndef QUEUE
#define QUEUE
#include <ostream>
#include <assert.h>
#include "transaction.h"

//---------------------------------------------------------------------------
// Class Queue
//
// ADT Queue: 
//   -- collection of zero or more items (list) with the restriction that
//      all insertions happen at one end, called the rear of the queue, 
//      and all removals occur at the other end, the front
//      (also known as FIFO -- First In, First Out)
//  
// Assumption:
//   -- Node (linked list implementation) is a struct made of just
//      a Transaction* and a Node*
//   -- data type inputed into the node should be actual Transaction data
//
// Implementation:
//   -- stores a lot of Transactions in through a linked list
//   -- nodes are created to hold each data type of Transaction when enqueue
//   -- enqueue adds a node to the rear end of the list
//   -- dequeue removes and returns a node from the front of the list
//---------------------------------------------------------------------------

using namespace std;

class Queue {

    // output operator
    friend ostream &operator<<(ostream &, const Queue &);

public:
    Queue();                // default constructor
    ~Queue();               // destructor
    void clear();           // clear out queue
    bool isEmpty() const;   // is the queue empty?

    // insert item, assume object passed in is valid, 
    // return whether successful
    bool enqueue(Transaction*);

    // remove item, parameter is removed item, 
    // return whether item is removed 
    bool dequeue(Transaction*&);

    // retrieve item, parameter is item at top, 
    // return whether item exists
    bool peek(Transaction*&) const;
private:

    // Node that has transaction data and next node
    struct Node {
        Transaction* data;
        Node* next;
    };

    // for linked list implementation
    Node* front;            // pointer to front of queue
    Node* rear;             // pointer to rear of queue
};
#endif // !QUEUE


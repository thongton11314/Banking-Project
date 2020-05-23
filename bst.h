#pragma once
#ifndef CLIENT_CONTAINER
#define CLIENT_CONTAINER
#include "client.h"

// Asumption?
// What ADT use ? bst

class BSTree {
public:
    BSTree();
    ~BSTree(); // calls makeEmpty which deallocates all memory
    
    // insert object into the tree, parameter holds pointer to object to insert
    bool insert(Client*);
    
    // retrieve object, first parameter is object to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const Client&, Client*&) const;
    void display() const;            //displays the contents of a tree to cout
    void makeEmpty();                //empties the current tree, deallocates all memory
    bool isEmpty() const;            //returns true if tree is empty

private:
    void recursiveHelper();          // use for traverse the tree

    struct Node {
        Client* data;
        Node* right;
        Node* left;
    };
    Node* root;                      // root of the tree
};
#endif // !CLIENT_CONTAINER


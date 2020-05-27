#pragma once
#ifndef CLIENT_CONTAINER
#define CLIENT_CONTAINER
#include <iostream>
#include "client.h"

// ADT Binary Search Tree
//
// Assumption:
//  - All keys in left subtree of a key must be smaller.
//  - All keys in right subtree must be greater.
//  - It has distinct keys and duplicates are not allowed.
//  - If the passed in node is already in tree, it will be deleted

// Implementation:
//  - Function insert, retrieve, display, makeEmpty will need sub-function to
//    help it traverse the tree recursively, 
//    insertHelper, retrieveHelper, displayHelper, emptyHelper will be called.

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
    
    struct Node {
        Client* data;
        Node* right;
        Node* left;
    };
    Node* root;                      // root of the tree

    // use for traverse the tree to add node
    // first parameter is new node, second is for traversing
    bool insertHelper(Client *, Node *&);

    // use for retrieve the node node
    // first parameter is target
    // second is for retriever
    // third parameter is for traversing
    bool retrieveHelper(const Client &, Client *&, Node*) const;

    // use for treverse the tree to coud
    void displayHelper(Node *) const;

    // use for traverse the tree to delete node
    void makeEmptyHelper(Node *&);

};
#endif // !CLIENT_CONTAINER


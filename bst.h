#pragma once
#ifndef CLIENT_CONTAINER
#define CLIENT_CONTAINER
#include <iostream>
#include <assert.h>
#include "client.h"

//---------------------------------------------------------------------------
// Class BST
// ADT Binary Search Tree:
//   -- A binary tree is defined as a tree in which no node can have more 
//      than two children. The highest degree of any node is two. This 
//      indicates that the degree of a binary tree is zero, one, or two
//
// Assumption:
//   -- All node in left subtree of a node must be smaller.
//   -- All node in right subtree must be greater.
//   -- It has distinct node and duplicates are not allowed.
//   -- If the passed in node is already in tree, it will be deleted
//
// Implementation:
//   -- Function insert, retrieve, display, makeEmpty will need 
//      sub-function to help it traverse the tree recursively, insertHelper
//      retrieveHelper, displayHelper, emptyHelper will be called.
//---------------------------------------------------------------------------

class BSTree {
public:
    BSTree();  // constructor
    ~BSTree(); // calls makeEmpty which deallocates all memory
    bool insert(Client*);   // insert object into the tree
    bool retrieve(const Client&, Client*&) const;     // retrieve object
    void display() const;   // displays the contents of a tree to cout
    void makeEmpty();       // empty the current tree, deallocates all memory
    bool isEmpty() const;   // returns true if tree is empty

private:
    
    // node that has client data and left,right node
    struct Node {
        Client* data;
        Node* right;
        Node* left;
    };

    Node* root;             // root of the tree

    // use for traverse recursively tree, then add node
    // first parameter is new node
    // second is for traversing
    bool insertHelper(Client *, Node *&);

    // use for traversing recursive tree, then retrieve the node
    // first parameter is root
    // second is for target
    // third parameter is pointer point to target
    bool retrieveHelper(Node*, const Client &, Client*&) const;

    // use for traverse recursively tree, then print out data
    void displayHelper(Node *) const;

    // use for traverse recursively tree, then delete every node
    void makeEmptyHelper(Node *&);

};
#endif // !CLIENT_CONTAINER
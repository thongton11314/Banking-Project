#pragma once
#ifndef CLIENT_CONTAINER
#define CLIENT_CONTAINER
#include <iostream>
#include "client.h"

class BSTree {
public:
    BSTree();
    ~BSTree();  
    bool insert(Client*);    
    bool retrieve(const Client&, Client*&) const;
    void display() const;
    void makeEmpty();
    bool isEmpty() const;
    
private:    
    struct Node {
        Client* data;
        Node* right;
        Node* left;
    };
    Node* root;                   
    bool insertHelper(Client *, Node *&);
    bool retrieveHelper(const Client &, Client *&, Node*) const;
    void displayHelper(Node *) const;
    void makeEmptyHelper(Node *&);

};
#endif

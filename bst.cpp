#include "bst.h"

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    makeEmpty();
}

bool BSTree::insert(Client * newClient) {

    // if tree is empty, this is the first node of tree
    if (root == nullptr) {

        // new node data for root. Left, right subtree are null pointer
        root = new Node{ newClient, nullptr, nullptr };
        return true;
    }

    // if tree is not empty
    else
        return insertHelper(newClient, root);
}

bool BSTree::insertHelper(Client * newClient, Node *& current) {
    // base case
    if (current == nullptr) {
        current = new Node{ newClient, nullptr, nullptr };
        return true;
    }

    // travere left
    else if (*newClient < *current->data) {
        return insertHelper(newClient, current->left);
    }

    // traverse right
    else if (*newClient > *current->data) {
        return insertHelper(newClient, current->right);
    }

    // duplicate is not allow, it will be deleted
    else {
        delete newClient;
        return false;
    }
}

bool BSTree::retrieve(const Client & target, Client *& ptr) const {
    
    // return true if retrieve successfully, else return false
    return retrieveHelper(target, ptr, root);
}


bool BSTree::retrieveHelper(const Client & target, Client *& retriever, Node * current) const {
    
    // if not found target
    if (current == nullptr) {
        retriever = nullptr;
        return false;
    }

    // travere left
    if (target < *current->data) {
        return retrieveHelper(target, retriever, current->left);
    }

    // traverse right
    else if (target > *current->data) {
        return retrieveHelper(target, retriever, current->right);
    }

    // if found target
    else {
        retriever = current->data;
        return true;
    }
}

void BSTree::display() const {

    // display the tree from left to right
    displayHelper(root);
}

void BSTree::displayHelper(Node * current) const {
    
    // base case
    if (current == nullptr)
        return;

    // recursive print in increasing order
    else {
        displayHelper(current->left);
        std::cout << *current->data << std::endl;
        displayHelper(current->right);
    }
}

void BSTree::makeEmpty() {

    // early exit if root is null pointer
    if (root == nullptr)
        return;

    // delete every node
    makeEmptyHelper(root);

    // always make root become null pointer
    root = nullptr;
}

void BSTree::makeEmptyHelper(Node *& current) {
    
    // delete every node
    if (current != nullptr) {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);
        delete current->data;   // delete node data
        delete current;         // delete node
    }
}

bool BSTree::isEmpty() const {
    return root == nullptr;
}

#include "bst.h"

//----------------------------------------------------------------------------
// constructor
// initialize the root
BSTree::BSTree() {
    root = nullptr;
}

//----------------------------------------------------------------------------
// deconstructor
// call makeEmpty to delete every node
BSTree::~BSTree() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// insert
// call the insertHelper to traverse recursively
// the passed in node will be taken and insert in tree
// insert new node to left or right subtree
// if the node is already in tree, return false
bool BSTree::insert(Client * newClient) {

    // first node if tree is empty
    if (root == nullptr) {

        // add new client, and assign left and right subtree null pointer
        root = new Node{ newClient, nullptr, nullptr };
        assert(root != nullptr); // out of memory
        return true;
    }

    // tree already has root
    else
        return insertHelper(newClient, root);
}

//----------------------------------------------------------------------------
// insertHelper
// traverse recursively the tree
// this function is sub-function of insert
bool BSTree::insertHelper(Client * newClient, Node *& current) {
    
    // base case
    if (current == nullptr) {
        current = new Node{ newClient, nullptr, nullptr };
        assert(current != nullptr); // out of memory
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

    // duplicate is not allowed
    else {
        return false;
    }
}

//----------------------------------------------------------------------------
// retrieve
// retrieve the node that match with target
// call the retrieveHelper to traverse recursively
// return true if retrieve successfully
//        false target not in tree
bool BSTree::retrieve(const Client & target, Client *& retriever) const {
    
    // find the target by traversing recursively
    return retrieveHelper(root, target, retriever);
}

//----------------------------------------------------------------------------
// retrieveHelper
// recursively traverse the tree
// this function is sub-function of retrieve
// return true if found the target
//        false if not found the target
bool BSTree::retrieveHelper(Node* current, 
                            const Client & target,
                            Client *& retriever) const {
    
    // target not found
    if (current == nullptr) {
        retriever = nullptr;
        return false;
    }

    // travere left-sub tree
    if (target < *current->data) {
        return retrieveHelper(current->left, target, retriever);
    }

    // traverse right-sub tree
    else if (target > *current->data) {
        return retrieveHelper(current->right, target, retriever);
    }

    // target is found
    else {
        retriever = current->data;
        return true;
    }
}

//----------------------------------------------------------------------------
// display
// display the node of tree from left to right
// call the displayHelper to perform traverse recursively
void BSTree::display() const {

    // display the tree from left to right
    displayHelper(root);
}

// displayHelper
// traverse recursively the tree
// this function is sub-function of display
void BSTree::displayHelper(Node * current) const {
    
    // base case
    if (current == nullptr)
        return;

    // print from left to right subtree
    else {
        displayHelper(current->left);
        std::cout << *current->data << std::endl;
        displayHelper(current->right);
    }
}

//----------------------------------------------------------------------------
// makeEmpty
// delete every node from the tree
// this function also will be called when deconstructor is called
void BSTree::makeEmpty() {

    // early exit, tree is empty
    if (root == nullptr)
        return;

    // tree not empty
    // delete every node
    makeEmptyHelper(root);

    // root always null pointer
    root = nullptr;
}

//----------------------------------------------------------------------------
// makeEmptyHelper
// traverse recursively the tree
// this function is sub-function of makeEmpty
void BSTree::makeEmptyHelper(Node *& current) {
    
    // delete every node
    if (current != nullptr) {
        makeEmptyHelper(current->left);   // traverse left
        makeEmptyHelper(current->right);  // traverse right
        delete current->data;             // delete node data
        delete current;                   // delete node
    }
}

//----------------------------------------------------------------------------
// isEmpty
// check tree is empty or not
bool BSTree::isEmpty() const {
    return root == nullptr;
}
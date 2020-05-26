#include "bst.h"
bool BSTree::insert(Client* dataptr) {
   Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) {             // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }
   }
   return true;
}

Client retrieve(int acc) const {
    if(root.getID() == acc) {
        
        return root;
    }
    else {
        return retrieveHelper(acc, root);
    }
}

Client retrieveHelper(int acc, Client*& ptr) const {
    if (ptr.getID() == data.getID()) {
        return ptr.data;
    }
    if(root->left != nullptr && root->left != nullptr) {
        retrieveHelper(acc, root->left);
        retrieveHelper(acc, root->right);
    }
    else if (root->left != nullptr) {
        retrieveHelper(acc, root->left);
    }
    else if (root->left != nullptr) {
        retrieveHelper(acc, root->right);
    }
    else {
        return nullptr;
    }
}
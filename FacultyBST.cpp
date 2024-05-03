#include "FacultyBST.h"

void FacultyBST::print(){
    printHelper(LazyBST::getRoot());
}

void FacultyBST::printHelper(TreeNode<Faculty*>* node){
    if (node== NULL)
        return;

    printHelper(node->left);
    node->key->print();
    printHelper(node->right);
}

Faculty* FacultyBST::search(int idNum){
    if(LazyBST::isEmpty())
        return NULL;
    
    TreeNode<Faculty*> *current = LazyBST::getRoot();

    while(current->key->getID() != idNum){
        if(idNum < current->key->getID()){ //TODO: current->key correct?
            current = current->left;
        }
        else{
            current = current->right;
        }

        if(current == NULL){
            return NULL;
        }
    }
    return current->key;
}

void FacultyBST::recDeleteHelper(TreeNode<Faculty*> *node){
    if (node != NULL) {
        recDeleteHelper(node->right);
        delete node->right->key;
        node->right = NULL;
        recDeleteHelper(node->left);
        delete node->left->key;
        node->left = NULL;
        delete node;
    }
    return;
}
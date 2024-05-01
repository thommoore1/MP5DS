#include "StudentBST.h"

void StudentBST::print(){
    printHelper(LazyBST::getRoot());
}

void StudentBST::printHelper(TreeNode<Student*>* node){
    if (node== NULL)
        return;

    printHelper(node->left);
    node->key->print();
    printHelper(node->right);
}

Student* StudentBST::search(int idNum){
    if(LazyBST::isEmpty())
        return NULL;
    
    TreeNode<Student*> *current = LazyBST::getRoot();

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
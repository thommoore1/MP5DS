#include "StudentBST.h"

void StudentBST::print(){
    printHelper(LazyBST::getRoot());
}

void StudentBST::printHelper(TreeNode<Student*>* node){ //prints data in order
    if (node== NULL)
        return;

    printHelper(node->left);
    node->key->print();
    printHelper(node->right);
}

Student* StudentBST::search(int idNum){ //special search method that searches based on the studentIDs number, because we do not want to search based on key
    if(LazyBST::isEmpty())
        return NULL;
    
    TreeNode<Student*> *current = LazyBST::getRoot();

    while(current->key->getID() != idNum){
        if(idNum < current->key->getID()){
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
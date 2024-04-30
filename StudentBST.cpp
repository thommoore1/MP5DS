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
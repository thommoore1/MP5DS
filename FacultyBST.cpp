#include "FacultyBST.h"

FacultyBST::FacultyBST(){
    Base::LazyBST<Faculty>();
}

void FacultyBST::print(TreeNode<Faculty*> *node){
    if (node== NULL)
        return;

    print(node->left);
    node->key->print();
    print(node->right);
}
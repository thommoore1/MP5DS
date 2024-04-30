#include "FacultyBST.h"

FacultyBST::FacultyBST() : LazyBST<Faculty>(){
    Base::LazyBST<>();
}

void FacultyBST::print(TreeNode<Faculty*> *node){
    if (node== NULL)
        return;

    print(node->left);
    node->key->print();
    print(node->right);
}
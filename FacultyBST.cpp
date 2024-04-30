#include "FacultyBST.h"

// FacultyBST::FacultyBST() : LazyBST<Faculty>(){
//     LazyBST::LazyBST<Faculty>();
// }

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
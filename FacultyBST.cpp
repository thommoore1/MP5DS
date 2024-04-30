#include "FacultyBST.h"

void FacultyBST::print(TreeNode<Faculty*> *node){
    if (node== NULL)
        return;

    print(node->left);
    node->key->print();
    print(node->right);
}
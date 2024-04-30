#include "StudentBST.h"

void StudentBST::print(TreeNode<Student*>* node){
    if (node== NULL)
        return;

    print(node->left);
    node->key->print();
    print(node->right);
}
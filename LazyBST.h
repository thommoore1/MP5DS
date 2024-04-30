#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
using namespace std;

/*
 TREENODE CLASS for LAZY BST
*/
template <typename T>
class TreeNode {
public:
    TreeNode();
    TreeNode(T k);
    virtual ~TreeNode();
    void updateDepths();
    int getDepth(TreeNode<T> *node);

    T key; // key = data
    TreeNode<T> *left;
    TreeNode<T> *right;
    int leftDepth;
    int rightDepth;
};

template <typename T>
TreeNode<T>::TreeNode() {
    left = NULL;
    right = NULL;
    key = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T k) {
    left = NULL;
    right = NULL;
    key = k;
}

template <typename T>
TreeNode<T>::~TreeNode() {
    left = NULL;
    right = NULL;
}

template <class T>
void TreeNode<T>::updateDepths() {
    // get max depth of each tree and update it
    rightDepth = getDepth(right);
    leftDepth = getDepth(left);
}

template <class T>
int TreeNode<T>::getDepth(TreeNode<T> *node) {
    if (node != NULL) {
        // greatest depth of left and right subtrees
        node->rightDepth = getDepth(node->right);
        node->leftDepth = getDepth(node->left);
        return max(node->leftDepth, node->rightDepth) + 1;
    }
    return 0;
}

template <typename T>
class LazyBST {
    LazyBST(); // empty tree
    virtual ~LazyBST();
    void insert(T value);
    bool contains(T value);
    bool deleteNode(T k);
    TreeNode<T> *getSuccessor(TreeNode<T> *d); // this method for finding the successor of the node about to be deleted
    void rebuild();

    bool isEmpty();
    T* getMin();
    T* getMax();

    void printTree();
    void recPrint(TreeNode<T> *node);
    void recDelete(TreeNode<T> *node); // used for deleting the entire tree

private:
    TreeNode<T> *root;

};

template <typename T>
LazyBST<T>::LazyBST() {
    root = NULL;
}

template <class T>
LazyBST<T>::~LazyBST() {
    // deletes the root node
    if (root != NULL) {
        recDelete(root);
    }
}

template <class T>
void LazyBST<T>::recDelete(TreeNode<T> *node) {
    if (node != NULL) {
        recDelete(node->right);
        recDelete(node->left);
        delete node;
    }
    return;
}

template <class T>
void insert(T value) {
    TreeNode<T> *node = new TreeNode<T>(value);

    if (isEmpty()) {
        root = node;
    }
    else {
        // tree had 1+ nodes
        TreeNode<T> *current = root;
        TreeNode<T> *parent = root;

        while(true) {
            parent = current;
            
            if (value < current) {
                // go left
                current = current->left;

                if (current == NULL) {
                    // found the insertion point
                    parent->left = node;
                    break;
                }

            }
            else {
                current = current->right;

                if (current == NULL) {
                    // isertion point
                    parent->right = node;
                    break;
                }
            }
        }
    }
}



#endif //LAZYBST_H

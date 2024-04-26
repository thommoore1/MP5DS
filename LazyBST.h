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

private:
    TreeNode<T> *root;

};

#endif //LAZYBST_H

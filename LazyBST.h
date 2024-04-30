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
    root->updateDepths(); // updates depths of all nodes
}

template <class T>
bool LazyBST<T>::contains(T value) {

    if (isEmpty()) return false;

    TreeNode<T> *current = root;

    while(current->key != value) {
        if (val < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current == NULL) return false;
    }
    return true;

}

template <class T>
bool LazyBST<T>::deleteNode(T k) {

    if (isEmpty()) return false;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    // find the node to delete
    while (current->key != k) {
        parent = current;

        if (k < current->key) {
            isLeft = true;
            current = current->left;
        }
        else {
            isLeft = false;
            current = current->right;
        }

        if (current == NULL) return false;
    }

    // if we make it here, we have found the node to be deleted
    //! LEAF NODE CASE:
    if (current->left == NULL && current->right == NULL) {
        if (current == root) root = NULL; // null it if only node in tree
        else if (isLeft) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }

    }
    //! ONE LEFT CHILD CASE:
    else if (current->right == NULL) {
        if (current == root) {
            root = current->left;
        }
        else if (isLeft) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
    }
    //! ONE RIGHT CHILD CASE:
    else if (current->left == NULL) {
        if (current == root) {
            root = current->right;
        }
        else if (isLeft) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
    }
    //! TWO CHILDREN CASE:
    else {
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root) {
            root = successor;
        }
        else if (isLeft) {
            parent->left = successor;
        }
        else {
            parent->right = successor;
        }
        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    delete current;
    
    return true;

}


#endif //LAZYBST_H

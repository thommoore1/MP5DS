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




template <class T>
LazyBST<T>::LazyBST(){
    root = NULL;
}

template <class T>
LazyBST<T>::~LazyBST(){
    //build some character, too much character never did no wrong
}

template <class T>
void LazyBST<T>::recPrint(TreeNode<T> *node){
    if(node == NULL){
        return;
    }

    cout << node->ket << endl;
    recPrint(node->left);
    recPrint(node->right);
}

template <class T>
void LazyBST<T>::printTree(){
    recPrint(root);
}

template <class T>
bool LazyBST<T>::isEmpty(){
    return (root == NULL);
}

template <class T>
T* LazyBST<T>::getMin(){
    if(isEmpty()){
        return NULL;
    }

    TreeNode<T> *current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return &(current->key);
}

template <class T>
T* LazyBST<T>::getMax(){
    if(isEmpty()){
        return NULL;
    }

    TreeNode<T> *current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return &(current->key);
}

template <class T>
void LazyBST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty()){
        root = node;
    }
    else{
        TreeNode<T> *current = root;
        TreeNode<T> *parent = root;

        while(true){
            parent = current;
            
            if(value < current->key){
                current = current->left;
                if(current == NULL){
                    //we found the insertion point
                    parent->left = node;
                    break;
                }
            }
            else{
                //we go right
                current = current->right;

                if(current == NULL){
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template <class T>
bool LazyBST<T>::contains(T value){
    if(isempty())
        return false;
    
    TreeNode<T> *current = root;

    while(current->ket != value){
        if(value < current->){
            current = current->left;
        }
        else{
            current = current->right;
        }

        if(current == NULL){
            return false;
        }
    }
    return true;
}

template <class T>
bool LazyBST<T>::deleteNode(T k){
    if(isEmpty()){
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(current->key != k){
        parent = current;

        if(k < current->key){
            isLeft = true;
            current = current->left;
        }
        else{
            isLeft = false;
            current = current->right;
        }

        if(current == NULL){
            return false;
        }
    }

    //if we get here, then we found the node to be deleted

    /* node to be deleted is a leaf node (no children)*/
    if(current->left == NULL && current->right == NULL){
        if(current == root){
            root == NULL;
        }
        else if(isLeft){
            parent->left = NULL;
        }
        else{
            parent->right = NULL;
        }
    } /*nodes to be deleted has 1 child*/
    else if(current->right == NULL){
        //node has one child and its a left child
        if(current == root){
            root = current->left;
        }
        else if(isLeft){
            parent->left = current->left;
        }
        else{
            parent->right = current->left;
        }
    }
    else if(current->left == NULL){
        //node has one child and its a right child
        if(current == root){
            root = current->right;
        }
        else if(isLeft){
            parent->left = current->right;
        }
        else{
            parent->right = current->right;
        }
    }
    else{
        //when the node to be dleted has 2 children. at this point we begin to cry and take a 4 hour nap
        TreeNode<T> *successor = getSuccessor(current);

        if(current == root){
            root = successor;
        }
        else if(isLeft){
            parent->left = successor;
        }
        else{
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    
    delete current;
    return true;
}

template <class T>
//d is the node to be deleted
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> = d->right;

    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }

    //once we get here, we identified our successor
    //now we need to check if the successor is the descendant of the right child
    if(successor != d->right){
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

#endif

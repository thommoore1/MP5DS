#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include <cstdlib>
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
        return max(node->leftDepth, node->rightDepth) + 1; // adds one to account for this node
    }
    return 0;
}

template <typename T>
class LazyBST {

    public:
        LazyBST(); // empty tree
        virtual ~LazyBST();
        void insert(T value);
        bool contains(T value);
        bool deleteNode(T k);
        TreeNode<T>* getSuccessor(TreeNode<T> *d); // this method for finding the successor of the node about to be deleted
        void tryRebuild();

        bool isEmpty();
        T* getMin();
        T* getMax();

        void printTree();
        void recPrint(TreeNode<T> *node);
        void recDeleteHelper(TreeNode<T> *node); // used for deleting the entire tree
        void recDelete();

        TreeNode<T>* getRoot();

    private:
        bool rebalancing;
        int size;
        TreeNode<T> *root;
        int counterDone; // used to determine whether the array being built is done 

        void arrayBuilder(T* buildArray);
        int buildHelper(TreeNode<T>* node, T* buildArray, int index);
        void recRebuildInsert(T* buildArray, int lowerBound, int upperBound);

};

template <typename T>
TreeNode<T>* LazyBST<T>::getRoot(){
    return root;
}

template <typename T>
LazyBST<T>::LazyBST() {
    rebalancing = false;
    root = NULL;
}

template <typename T>
LazyBST<T>::~LazyBST() {
    // deletes the root node
    if (root != NULL) {
        recDelete();
        root = NULL;
    }
}

template <typename T>
void LazyBST<T>::recDelete(){
    recDeleteHelper(root);
    root = NULL;
}

template <typename T>
void LazyBST<T>::recDeleteHelper(TreeNode<T> *node) {
    if (node != NULL) {
        recDeleteHelper(node->right);
        node->right = NULL;
        recDeleteHelper(node->left);
        node->left = NULL;
        delete node;
    }
    return;
}

template <typename T>
void LazyBST<T>::recPrint(TreeNode<T> *node){
    if(node == NULL){
        return;
    }

    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}

template <typename T>
void LazyBST<T>::printTree(){
    recPrint(root);
}

template <typename T>
bool LazyBST<T>::isEmpty(){
    return (root == NULL);
}

template <typename T>
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

template <typename T>
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

template <typename T>
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
    root->updateDepths(); // update depths of tree
    ++size;
    if(!rebalancing){
        tryRebuild();
    }
}

template <typename T>
bool LazyBST<T>::contains(T value){
    if(isEmpty())
        return false;
    
    TreeNode<T> *current = root;

    while(current->key != value){
        if(value < current->key){ 
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

template <typename T>
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
            root = NULL;
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
    delete current->key;
    delete current;
    if(root != NULL){
        root->updateDepths(); // update depths of tree
    }
    --size;
    rebalancing = true;
    if(root != NULL){
        tryRebuild();
    }
    rebalancing = false;
    return true;
}

template <typename T>
//d is the node to be deleted
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right; 

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

template <typename T>
void LazyBST<T>::tryRebuild() {
    // check if conditions for rebuild are met
    int heightFactor = abs(root->rightDepth - root->leftDepth);
    if (heightFactor > 1.5) { 
        // make new array to temporarily store all values in BSTv
        T* rebuildArray = new T[size];
        arrayBuilder(rebuildArray);
        int median = 0;
        median = size/2;

        // delete contents (rec delete)
        recDelete();

        int sizeCopy = size;
        size = 0;

        // insert median
        //rebuildArray[0]->print();
        //rebuildArray[median]->print();
        rebalancing = true;
        insert(rebuildArray[median]);
        // new median (median/2)
        recRebuildInsert(rebuildArray, median+1, sizeCopy - 1);
        recRebuildInsert(rebuildArray, 0, median-1);
        rebalancing = false;

        // new median (original median + origmedian/2)

        // repeat previous 2 steps
        
        // iterate through array to 
        delete[] rebuildArray;
    }
}

template <typename T>
void LazyBST<T>::recRebuildInsert(T* rebuildArray, int lowerBound, int upperBound) {
    // if only one item left in array, insert it
    if (lowerBound >= upperBound) {
        insert(rebuildArray[lowerBound]);
        return;
    }
    // if two items left
    else if (upperBound - lowerBound == 1) {
        // insert both upper and lower bound
        insert(rebuildArray[lowerBound]);
        insert(rebuildArray[upperBound]);
        return;
    }
    int median = lowerBound + ((upperBound - lowerBound)/2);
    insert(rebuildArray[median]);
    // create new upper bound for the lower half (the one below this median)
    recRebuildInsert(rebuildArray, lowerBound, median - 1);
    // create nwe lower bound for the upper half (the one above this median)
    recRebuildInsert(rebuildArray, median + 1, upperBound);
}

template <typename T>
void LazyBST<T>::arrayBuilder(T* buildArray){
    buildHelper(root, buildArray, 0);
}

template <typename T>
int LazyBST<T>::buildHelper(TreeNode<T>* node, T* buildArray, int index) {
    if (node == NULL)
        return index;

    int newIndex = index;
    // passes in index to left, will be updated if not null
    newIndex = buildHelper(node->left, buildArray, newIndex);
    buildArray[newIndex++] = node->key; // updates index if there is a value here
    newIndex = buildHelper(node->right, buildArray, newIndex); // passes in index to the right
    return newIndex; // returns the final index
}

#endif

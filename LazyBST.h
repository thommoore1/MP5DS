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
    void recDelete(TreeNode<T> *node); // used for deleting the entire tree

    TreeNode<T>* getRoot();

private:
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
    root = NULL;
}

template <typename T>
LazyBST<T>::~LazyBST() {
    // deletes the root node
    if (root != NULL) {
        recDelete(root);
    }
}

template <typename T>
void LazyBST<T>::recDelete(TreeNode<T> *node) {
    if (node != NULL) {
        recDelete(node->right);
        recDelete(node->left);
        delete node;
    }
    return;
}

// template <typename T>
// bool LazyBST<T>::contains(T value) {

//     if (isEmpty()) return false;

//     TreeNode<T> *current = root;

//     while(current->key != value) {
//         if (value < current->key) {
//             current = current->left;
//         }
//         else {
//             current = current->right;
//         }

//         if (current == NULL) return false;
//     }
//     return true;

// }


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
    tryRebuild();
}

template <typename T>
bool LazyBST<T>::contains(T value){
    if(isEmpty())
        return false;
    
    TreeNode<T> *current = root;

    while(current->key != value){
        if(value < current->key){ //TODO: current->key correct?
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
    root->updateDepths(); // update depths of tree
    --size;
    tryRebuild();
    return true;
}

template <typename T>
//d is the node to be deleted
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> current = d->right; //TODO: CORRECT?

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
    double heightFactor = (double) root->rightDepth / (double) root->leftDepth;
    if (heightFactor > 1.5 || heightFactor < (0.666667)) { 
        // make new array to temporarily store all values in BSTv
        T* rebuildArray = new T*[size];
        arrayBuilder(rebuildArray);
        int median = size/2;

        // delete contents (rec delete)
        recDelete(root);

        // insert median
        insert(rebuildArray[median]);
        
        // new median (median/2)
        recRebuildInsert(rebuildArray, median+1, size);
        recRebuildInsert(rebuildArray, 0, median-1);

        // new median (original median + origmedian/2)

        // repeat previous 2 steps
        
        // iterate through array to 
    }
}

template <typename T>
void LazyBST<T>::recRebuildInsert(T* rebuildArray, int lowerBound, int upperBound) {
    if (lowerBound == upperBound) {
        insert(rebuildArray[lowerBound]);
        return;
    }
    else if (upperBound - lowerBound == 1) {
        // insert both upper and lower bound
    }
    int median = lowerBound + ((upperBound - lowerBound)/2);
    insert(median);
    recRebuildInsert()

}

template <typename T>
void LazyBST<T>::arrayBuilder(T* buildArray){
    printHelper(root, buildArray, 0);
}

template <typename T>
int LazyBST<T>::buildHelper(TreeNode<T>* node, T* buildArray, int index) {
    if (node == NULL)
        return index;

    int newIndex = index;
    // passes in index to left, will be updated if not null
    newIndex = printHelper(node->left, buildArray, newIndex);
    buildArray[newIndex++] = node->key; // updates index if there is a value here
    newIndex = printHelper(node->right, buildArray, newIndex); // passes in index to the right
    return newIndex; // returns the final index
}

#endif

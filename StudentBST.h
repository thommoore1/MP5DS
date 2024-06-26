#ifndef STUDENTBST_H
#define STUDENTBST_H

#include <iostream>

#include "LazyBST.h"
#include "DblList.h"
#include "Student.h"

using namespace std;

class StudentBST : public LazyBST<Student*>{
    public:
        //Student();
        void print();
        void printHelper(TreeNode<Student*>* node);
        Student* search(int idNum);
    private:
};

#endif
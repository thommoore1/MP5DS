#ifndef FACULTYBST_H
#define FACULTYBST_H

#include <iostream>

#include "LazyBST.h"
#include "DblList.h"
#include "Faculty.h"

using namespace std;

class FacultyBST : public LazyBST<Faculty>{
    public:
        FacultyBST();
        void print(TreeNode<Faculty*>* node);
    private:
};

#endif
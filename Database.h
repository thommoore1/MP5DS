#ifndef DATABASE_H
#define DATAH

#include <iostream>
#include <string>

#include "DblList.h"
#include "LazyBST.h"
#include "Faculty.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

class Database{
    public:
        Database();
        ~Database();
        void start();
    private:
        void print(LazyBST<Faculty>* bst);
        void print(LazyBST<Student>* bst);
};

#endif
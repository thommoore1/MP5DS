#ifndef DATABASE_H
#define DATAH

#include <iostream>
#include <string>

#include "DblList.h"
#include "LazyBST.h"
#include "Faculty.h"
#include "Student.h"
#include "Faculty.h"
#include "FacultyBST.h"
#include "StudentBST.h"

using namespace std;

class Database{
    public:
        Database();
        ~Database();
        void start();
};

#endif
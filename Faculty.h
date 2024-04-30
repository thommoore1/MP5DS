#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>

#include "DblList.h"

using namespace std;

class Faculty{
    public:
        Faculty(int id, string name, string level, string department, DblList<int>* studentIDs);
        ~Faculty();

        bool operator==(const Faculty& otherFaculty); //TODO: Faculty* instead of Faculty&?
        void print();
    private:
        int id;
        string name;
        string level;
        string department;
        DblList<int>* studentIDs;
};

#endif
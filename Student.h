#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
    public:
        Student(int id, string name, string level, string major, double gpa, int advisorID);
        ~Student();

        void print();
    private:
        int id;
        string name;
        string level;
        string major;
        double gpa;
        unsigned int advisorID;
};

#endif
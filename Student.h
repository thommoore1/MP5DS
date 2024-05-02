#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
    public:
        Student(int id, string name, string level, string major, double gpa, int advisorID);
        ~Student();
        bool operator==(const Student& otherStudent);
        bool operator<(const Student& otherStudent);
        bool operator!=(const Student& otherStudent);
        int getID();
        int getAdvisor();
        void setAdvisor(int advisorIDnew);

        void print();
    private:
        int id;
        string name;
        string level;
        string major;
        double gpa;
        int advisorID;

};

#endif
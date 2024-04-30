#include "Student.h"

Student::Student(int id, string name, string level, string major, double gpa, int advisorID){
    this->id = id;
    this->name = name;
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisorID = advisorID;
}

void Student::print(){
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << major << endl;
    cout << "Major: " << gpa << endl; 
    cout << "GPA: " << advisorID << endl << endl;
}

bool Student::operator == (const Student& otherStudent){
    return this->id == otherStudent.id;
}

bool Student::operator < (const Student& otherStudent){
    return this->id < otherStudent.id;
}


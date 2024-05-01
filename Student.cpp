#include "Student.h"

Student::Student(int id, string name, string level, string major, double gpa, int advisorID){
    this->id = id;
    this->name = name;
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisorID = advisorID;
}

Student::~Student(){
}

void Student::print(){
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "Major: " << major << endl; 
    cout << "GPA: " << gpa << endl;
    cout << "Advisor ID: " << advisorID << endl << endl;
}

bool Student::operator == (const Student& otherStudent){
    return this->id == otherStudent.id;
}

bool Student::operator < (const Student& otherStudent){
    return this->id < otherStudent.id;
}

bool Student::operator!=(const Student& otherStudent){
    return this->id != otherStudent.id;
}

int Student::getID(){
    return id;
}

int Student::getAdvisor(){
    return advisorID;
}

void Student::setAdvisor(int advisorIDnew){
    advisorID = advisorIDnew;
}
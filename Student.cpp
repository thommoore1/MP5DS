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


#include "Faculty.h"

Faculty::Faculty(int id, string name, string level, string department, DblList<int>* studentIDs){
    this->id = id;
    this->name = name;
    this->level = level;
    this->department = department;
    this->studentIDs = studentIDs;
}

void Faculty::print(){
    cout << "ID: " << id << endl; 
    cout << "Name: " << name << endl; 
    cout << "Level: " << level << endl; 
    cout << "Department: " << department << endl;
    
    cout << name << " is an advisor for the students with the IDS: " << endl;
    int data;
    int loop = 0;
    int firstID;

    while(!(studentIDs->isEmpty()) && studentIDs->getFront() != firstID){
        data = studentIDs->removeFront();

        if(loop == 0){
            firstID = data;
        }
        
        ++loop;
        cout << "   " << data << endl;
        studentIDs->insertBack(data);
    }
}

bool Faculty::operator == (const Faculty& otherFaculty){
    return this->id == otherFaculty.id;
}
bool Faculty::operator < (const Faculty& otherFaculty) {
    return this->id < otherFaculty.id;
}
bool Faculty::operator > (const Faculty& otherFaculty) {
    return this->id > otherFaculty.id;
}

bool Faculty::operator!=(const Faculty& otherFaculty){
    return this->id != otherFaculty.id;
}

int Faculty::getID(){
    return id;
}

void Faculty::removeStudent(int studentID){
    if(studentIDs->find(studentID) != -1){
        studentIDs->removeNode(studentID);
    }
}

void Faculty::addStudent(int studentID){
    studentIDs->insertBack(studentID);
}

Faculty::~Faculty(){

}
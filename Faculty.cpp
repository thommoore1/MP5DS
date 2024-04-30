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
    while(!studentIDs->isEmpty()){
        data = studentIDs->removeFront();
        cout << "   " << data << endl;
    }

}

Faculty::~Faculty(){

}
#include "Database.h"

Database::Database(){

}

void Database::start(){
    FacultyBST* facultyTree = new FacultyBST();
    StudentBST* studentTree = new StudentBST();

    int menuChoice = -1;
    int studentID;
    int facultyID;

    string name;
    string level;
    string major;
    double gpa;

    string department;

    string facultyStudentIDInput;

    while(menuChoice != 11){
        // prints all the choices
        cout << "---MAKE YOUR CHOICE!---" << endl << endl;
        cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3. Find and display student information given the student id" << endl;
        cout << "4. Find and display faculty information given the faculty id" << endl;
        cout << "5. Add a new student" << endl;
        cout << "6. Delete a student given the id" << endl;
        cout << "7. Add a new faculty member" << endl;
        cout << "8. Delete a faculty member given the id." << endl;
        cout << "9. Change a student’s advisor given the student id and the new faculty id." << endl;
        cout << "10. Remove an advisee from a faculty member given the id" << endl;

        cin >> menuChoice;
        // 1-2: printing for student and faculty
        if(menuChoice == 1){
            studentTree->print();
        }
        else if(menuChoice == 2){
            facultyTree->print();
        }
        // 3-4: searching for students or faculty
        else if(menuChoice == 3){
            cout << "Enter the student ID you would like to search for: ";
            cin >> studentID;
            studentTree->search(studentID)->print();
        }
        else if(menuChoice == 4){
            cout << "Enter the faculty ID you would like to search for: ";
            cin >> facultyID;
            facultyTree->search(facultyID)->print();
        }
        // 5: adding a new student
        else if(menuChoice == 5){
            cout << "Enter your student's ID, name, level, major, gpa, and their advisor's ID" << endl;
            cin >> studentID;
            cin >> name;
            cin >> level;
            cin >> major;
            cin >> gpa;
            cin >> facultyID;
            Student* insert = new Student(studentID, name, level, major, gpa, facultyID);
            studentTree->insert(insert);
        }
        // 6: student deletion
        else if(menuChoice == 6){
            cout << "Input the ID of the student you would like to delete" << endl;
            cin >> studentID;
            studentTree->deleteNode(studentTree->search(studentID));
        }
        // 7: new faculty
        else if(menuChoice == 7){
            cout << "Enter the id, name, level, department, and IDs of any students the faculty advises for. Enter EXfT when you have entered all students" << endl;
            cin >> facultyID;
            cin >> name;
            cin >> level;
            cin >> department;

            DblList<int>* studentList = new DblList<int>();

            cout << "Enter data: " << endl;
            cin >> facultyStudentIDInput;

            while(facultyStudentIDInput != "EXIT"){
                studentList->insertFront(stoi(facultyStudentIDInput));
                cout << "Enter data: " << endl;
                cin >> facultyStudentIDInput;
            }
            
            Faculty* insert = new Faculty(facultyID, name, level, department, studentList);
            facultyTree->insert(insert);
            studentList = NULL;
        }
        // 8: delete faculty
        else if(menuChoice == 8){
            cout << "Input the ID of the faculty you would like to delete" << endl;
            cin >> facultyID;
            facultyTree->deleteNode(facultyTree->search(facultyID));
        }
        // 9-10: change/remove advisor
        else if(menuChoice == 9){
            cout << "Enter the ID of the student whose advisor you would like to change, then the ID of that advisor" << endl;
            cin >> studentID;
            cin >> facultyID;
            facultyTree->search(studentTree->search(studentID)->getAdvisor())->removeStudent(studentID);
            studentTree->search(studentID)->setAdvisor(facultyID);
            facultyTree->search(facultyID)->addStudent(studentID);
        }
        else if(menuChoice == 10){
            cout << "Enter student ID you would like to remove, then the advisor ID you would like to remove them from" << endl;
            cin >> studentID;
            cin >> facultyID;
            facultyTree->search(facultyID)->removeStudent(studentID);
            studentTree->search(studentID)->setAdvisor(-1);
        }
    }
}

void Database::print(LazyBST<Faculty>* bst){
    
}

Database::~Database(){

}
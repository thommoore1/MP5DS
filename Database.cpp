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
        cout << "---MAKE YOUR CHOICE!---" << endl << endl;
        cout << "1.  Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2.  Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3.  Find and display student information given the student id" << endl;
        cout << "4.  Find and display faculty information given the faculty id" << endl;
        cout << "5.  Add a new student" << endl;
        cout << "6.  Delete a student given the id" << endl;
        cout << "7.  Add a new faculty member" << endl;
        cout << "8.  Delete a faculty member given the id." << endl;
        cout << "9.  Change a student’s advisor given the student id and the new faculty id." << endl;
        cout << "10. Remove an advisee from a faculty member given the id" << endl;
        cout << "11. Quit" << endl << endl;

        cin >> menuChoice;
        // 1-2: printing for student and faculty
        if(menuChoice == 1){
            studentTree->print(); //safe if nothing is presemt
        }
        else if(menuChoice == 2){
            facultyTree->print(); //safe if nothing is presemt
        }
        // 3-4: searching for students or faculty
        else if(menuChoice == 3){
            cout << "Enter the student ID you would like to search for: ";
            cin >> studentID;
            if(cin.fail()){
                cout << "Int was not entered. Please call this again to properly print" << endl << endl;
            }
            else{
                studentTree->search(studentID)->print();
            }
        }
        else if(menuChoice == 4){
            cout << "Enter the faculty ID you would like to search for: ";
            cin >> facultyID;
            if(cin.fail()){
                cout << "Int was not entered. Please call this again to properly print" << endl << endl;
            }
            else{
                facultyTree->search(facultyID)->print();
            }
        }
        // 5: adding a new student
        else if(menuChoice == 5){
            cout << "Enter your student's ID, name, level, major, gpa, and their advisor's ID" << endl;
            while(true){
                cin >> studentID;
                cin >> name;
                cin >> level;
                cin >> major;
                cin >> gpa;
                cin >> facultyID;
                if(cin.fail()){
                    cout << endl << "Invalid Input. Please try again." << endl
                         << "Enter your student's ID, name, level, major, gpa, and their advisor's ID" << endl << endl;
                    cin.clear();
                    string fix; //read the invalid input into it
                    getline(cin, fix);
                }
                else{
                    break;
                }
            }
            Student* insert = new Student(studentID, name, level, major, gpa, facultyID);
            studentTree->insert(insert);
        }
        else if(menuChoice == 6){
            cout << "Input the ID of the student you would like to delete" << endl;
            cin >> studentID;
            studentTree->deleteNode(studentTree->search(studentID));
            cout << endl;
        }
        else if(menuChoice == 7){
            cout << "Enter the id, name, level, department, and IDs of any students the faculty advises for. Enter anything other an int when all students are entered" << endl;
            while (true) {
                cin >> facultyID;
                cin >> name;
                cin >> level;
                cin >> department;
                
                if (cin.fail()) {
                    cout << endl << "Invalid Input. Please try again." << endl
                         << "Enter the advisor's ID, name, level, department, and any IDs of the students the faculty advises for. Enter anything other an int to exit when all students are entered" << endl << endl;
                    cin.clear();
                    string fix; //read the invalid input into it
                    getline(cin, fix);
                }
                else{
                    break;
                } 
            }

            DblList<int>* studentList = new DblList<int>();

            cout << "Enter student ID: " << endl;
            cin >> facultyStudentIDInput;

            while (true) {
                // tries to get an int for student ID. If not, it'll finish adding student IDs
                try {
                    stoi(facultyStudentIDInput);
                }
                catch (exception &excpt) {
                    cout << "Finished with student ID input. " << endl << endl;
                    break;
                }
                
                // get more student nums
                studentList->insertFront(stoi(facultyStudentIDInput));
                cout << "Enter student ID: " << endl;
                cin >> facultyStudentIDInput;

            }

            // adds the faculty to the list
            Faculty* insert = new Faculty(facultyID, name, level, department, studentList);
            facultyTree->insert(insert);
            studentList = NULL;
        }
        else if(menuChoice == 8){
            cout << "Input the ID of the faculty you would like to delete" << endl;
            if(cin.fail()){
                cout << "Int was not entered. Please call this again to properly print" << endl << endl;
            }
            else{
                cin >> facultyID;
                if(facultyTree->search(facultyID) == NULL){
                    cout << "Could not find the faculty ID" << endl;
                }
                else{
                    facultyTree->deleteNode(facultyTree->search(facultyID));
                }
            }
        }
        else if(menuChoice == 9){
            cout << "Enter the ID of the student whose advisor you would like to change, then the ID of that advisor" << endl;
            cin >> studentID;
            cin >> facultyID;
            if(cin.fail()){
                cout << "Int was not entered. Please call this again to properly print" << endl << endl;
            }
            else{
                if (studentTree->search(studentID) == NULL || facultyTree->search(facultyID) == NULL){
                    cout << "Student ID or Faculty ID did not exist. Please try again" << endl << endl;
                }
                else if (facultyTree->search(studentTree->search(studentID)->getAdvisor()) != NULL){ // If student's old advisor exists
                    facultyTree->search(studentTree->search(studentID)->getAdvisor())->removeStudent(studentID);
                    studentTree->search(studentID)->setAdvisor(facultyID);
                    facultyTree->search(facultyID)->addStudent(studentID);
                }
                else { //If student's old advisor does not exist
                    studentTree->search(studentID)->setAdvisor(facultyID);
                    facultyTree->search(facultyID)->addStudent(studentID);
                }
            }
        }
        else if(menuChoice == 10){
            cout << "Enter student ID you would like to remove, then the advisor ID you would like to remove them from" << endl;
            cin >> studentID;
            cin >> facultyID;
            if(cin.fail()){
                cout << "Int was not entered. Please call this again to properly print" << endl << endl;
            }
            else{
                if(facultyTree->search(facultyID) == NULL || studentTree->search(studentID) == NULL){
                    cout << "Student ID or Faculty ID did not exist. Please try again" << endl << endl;
                }
                else{
                    facultyTree->search(facultyID)->removeStudent(studentID); //remove student is safe incase student doesn't exist
                    studentTree->search(studentID)->setAdvisor(-1);
                }
            }
        }
    }
}

void Database::print(LazyBST<Faculty>* bst){
    
}

Database::~Database(){

}
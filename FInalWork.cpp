#include <iostream>
#include<vector>
#include <limits>
#include <iomanip>
#include <cstdlib>
using namespace std;
struct Course {
	int courseNo;
	string course_title;
	int crh;
	string grade=" ";
	Course *nextCourse;

}*headCourse = NULL;

struct Student{
	int id;
	string first_name;
	string last_name;
	int age;
	string sex;
	Course *courses=NULL;
	Student *nextStudent;
}*headStudent = NULL;

// Function definitions

void printFooter() {
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                 Successfully Finished            |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}
void clearScreen() {
    system("cls");
}

void printHeader() {
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                 Student Management               |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}

bool checkStudent(int id){
	if(headStudent == NULL){
		return false;
	}
	else {
		Student *tempStudent = headStudent;
		while(tempStudent != NULL){
			if(tempStudent->id == id){
				return true;
			}
			tempStudent = tempStudent->nextStudent;
		}
	}
	return false;
	
}
bool checkCourse(int courseNO){
	if(headCourse == NULL){
		return false;
	}
	else {
		Course *tempCourse = headCourse;
		while(tempCourse != NULL){
			if(tempCourse->courseNo == courseNO){
				return true;
			}
			tempCourse = tempCourse->nextCourse;
		}
	}
	return false;
}
void registerStudent()
{
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                Register a student                |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    Student *temp_student = new Student;
    int temp_id;
    cout << "Insert the ID of the student (positive integer): "<<endl;
    cout<< "-------------------------------------------------";
    while (!(cin >> temp_id) || temp_id < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    if(checkStudent(temp_id)){
        cout << "Error: The student with ID " << temp_id << " already exists in the database." << endl;
    }
    else {
        temp_student->id = temp_id;
        cout << "Enter the first name of the student: "<<endl;
        cout<< "-------------------------------------";
        while(!(cin >> temp_student->first_name)){
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Invalid input. One word Only";
		}
        cout << "Enter the last name of the student: "<<endl;
        cout<< "-------------------------------------";
        while(!(cin >> temp_student->last_name)){
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	cout << "Invalid input. One word Only";
		}
        cout << "\nEnter the age of the student (between 18 and 60 years): "<<endl;
        cout<< "--------------------------------------------------------";
        while (!(cin >> temp_student->age) || temp_student->age < 18 || temp_student->age > 60) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer between 18 and 60: ";
        }
        cout << "\nEnter the sex of the student (M/F): "<<endl;
        cout<< "-------------------------------------";
        while (!(cin >> temp_student->sex) || (temp_student->sex != "M" && temp_student->sex != "F")) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter either 'M' or 'F': ";
        }
        temp_student->nextStudent = headStudent;
        headStudent = temp_student;
        cout << "Student with ID " << temp_id << " registered successfully." << endl;
        printFooter();
    }
}

void registerCourse(){
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                Register a course                 |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    int temp_id;
    cout << "Insert the Id of course: ";
    while (!(cin >> temp_id) || temp_id < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    if(checkCourse(temp_id)){
        cout << "Error: The course with ID " << temp_id << " already exists in the database." << endl;
    }
    else {
        Course *temp_course = new Course;
        temp_course->courseNo = temp_id;
        cout << "Enter the name of the course: ";
        cin.ignore();
        getline(cin ,temp_course->course_title);
        cout << "Enter the the credit hour of the course: ";
        while (!(cin >> temp_course->crh) || temp_course->crh < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive integer: ";
        }
        temp_course->nextCourse = headCourse;
        headCourse = temp_course;
        printFooter();
    }
}

void registerStudentForAcourse() {
	
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|             Register a student for a course       |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    int studentId, courseNo;
    cout << "Enter the Id of a student: ";
    while (!(cin >> studentId) || studentId < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    cout << "Enter the courseNo of a Course: ";
    while (!(cin >> courseNo) || courseNo < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }

    Student* currentStudent = headStudent;
    while (currentStudent != NULL && currentStudent->id != studentId) {
        currentStudent = currentStudent->nextStudent;
    }
    Course* currentCourse = headCourse;
    while (currentCourse != NULL && currentCourse->courseNo != courseNo) {
        currentCourse = currentCourse->nextCourse;
    }
    if (currentStudent != NULL && currentCourse != NULL) {
        Course* newCourse = new Course;
        newCourse->courseNo = currentCourse->courseNo;
        newCourse->course_title = currentCourse->course_title;
        newCourse->nextCourse = currentStudent->courses;
        currentStudent->courses = newCourse;
    }
    
    cout << currentStudent->first_name << " is registered for " << currentCourse->course_title << " successfully." << endl;
	printFooter();
}

void displayStudent() {
	
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                 Display a student                |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    int id;
    cout << "Please enter the ID of the student you wish to view: ";
    cin >> id;

    // Find the student with the given ID
    Student* currentStudent = headStudent;
    while (currentStudent != NULL && currentStudent->id != id) {
        currentStudent = currentStudent->nextStudent;
    }

    // If the student is found, display their information
    if (currentStudent != NULL) {
    	cout<<"+-------------------------------------------+"<<endl;
        cout << "| Name: " << currentStudent->first_name << " " << currentStudent->last_name <<" | "<< endl;
        cout << "| ID: " << currentStudent->id << " | "<<endl;
        if (currentStudent->courses!=NULL){
			cout << "| Registerd for:"<<endl;
			cout << "|        --+ "<<currentStudent ->courses->course_title <<" | "<<endl;
			if (currentStudent ->courses->grade!=" ")
				cout << "|        --+ "<<currentStudent ->courses->grade <<" | "<<endl;
		}else{
			cout << "| Has't registered for any courses   ||"<<endl;
		}

    } else {
        cout << "No student with ID " << id << " was found." << endl;
    }

    cout << "******************************************************************************************" << endl;
}

void displayCourse(){
	
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                  Display a course                |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    int id;
    cout << "Enter the course number of a course: ";
    cin >> id;

    Course* currentCourse = headCourse;
    while (currentCourse != NULL && currentCourse->courseNo != id) {
        currentCourse = currentCourse->nextCourse;
    }

    if (currentCourse == NULL) {
        cout << "Error: Course not found." << endl;
        return;
    }

    // Display table header
    cout << "==========================================================================" << endl;
    cout << "|| Course Number || Course Title                                 || CRH ||" << endl;
    cout << "==========================================================================" << endl;

    // Display course information in table format
    printf("|| %-13d || %-45s || %-4d ||\n", currentCourse->courseNo, currentCourse->course_title.c_str(), currentCourse->crh);

    cout << "==========================================================================" << endl;
}

void printHeaders() {
    cout << "+----+-----------------+-----------------+-----+------+----------------------------+" << endl;
    cout << "| ID |    First Name   |    Last Name    | Age | Sex  |          Course            |" << endl;
    cout << "+----+-----------------+-----------------+-----+------+----------------------------+" << endl;
}

void printStudent(Student *s) {
	if(s->courses!=NULL)
    	cout << "| " << setw(2) << s->id << " | " << setw(15) << s->first_name << " | " << setw(15) << s->last_name << " | " << setw(3) << s->age << " | " << setw(4) << s->sex << " | " << setw(15) << s->courses->course_title << " | " << endl;
	else
		cout << "| " << setw(2) << s->id << " | " << setw(15) << s->first_name << " | " << setw(15) << s->last_name << " | " << setw(3) << s->age << " | " << setw(4) << s->sex << " | " << setw(4) <<"NONE" << " | "<< endl;
}

void displayStudents() {
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                Display all students              |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    clearScreen();
    printHeaders();
    Student *curr = headStudent;
    while(curr != NULL) {
        printStudent(curr);
        curr = curr->nextStudent;
    }
    cout << "+----+-----------------+-----------------+-----+------+-------+" << endl;
}
void sortStudents() {
    if (headStudent == NULL) {
        cout<<"|----------------------------|"<<endl;
		cout<<"| No students registered yet |" << endl;
		cout<<"|----------------------------|"<<endl;
        return;
    }
    // Sort the students by their first name
    for (Student *a = headStudent; a->nextStudent != NULL; a = a->nextStudent) {
        for (Student *b = a->nextStudent; b != NULL; b = b->nextStudent) {
            if (a->first_name > b->first_name) {
                swap(a->id, b->id);
                swap(a->first_name, b->first_name);
                swap(a->last_name, b->last_name);
                swap(a->age, b->age);
                swap(a->sex, b->sex);
            }
        }
    }

    // Display the sorted students and their courses
    cout << "+----+---------------+--------------+-----+------++" << endl;
    cout << "| ID |   First Name  |   Last Name  | Age | Sex  ||" << endl;
    cout << "+----+---------------+--------------+-----+------++" << endl;

    for (Student *currentStudent = headStudent; currentStudent != NULL; currentStudent = currentStudent->nextStudent) {
            cout << "| " << setw(2) << currentStudent->id << " | "
                 << setw(13) << currentStudent->first_name << " | "
                 << setw(12) << currentStudent->last_name << " | "
                 << setw(3) << currentStudent->age << " | "
                 << setw(4) << currentStudent->sex << " | "<<endl;
        cout << "+----+---------------+--------------+-----+------++" << endl;
    }
}
void deleteStuById() {
	
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|               Delete student by ID               |" << endl;
    cout << "+--------------------------------------------------+" << endl;
	int id;
	cout << "Enter the id of a student " << endl;
	cin >> id;
	
    if (headStudent == NULL) {
    	cout<<"|------------------------------------------|"<<endl;
        cout << "| Student with ID " << id << " not found.   |" << endl;
        cout<<"|------------------------------------------|"<<endl;
        return;
    }
    if (headStudent->id == id) {
        Student* temp = headStudent;
        headStudent = headStudent->nextStudent;
        delete temp;
        cout<<"|------------------------------------------------------|"<<endl;
	    cout << "| Student with ID " << id << " Deleted Successfully. |" << endl;
	    cout<<"|------------------------------------------------------|"<<endl;
        return;
    }
    Student* prev = headStudent;
    Student* curr = headStudent->nextStudent;
    while (curr != NULL) {
        if (curr->id == id) {
            prev->nextStudent = curr->nextStudent;
            cout<<"|------------------------------------------------------|"<<endl;
		    cout << "| Student with ID " << id << " Deleted Successfully. |" << endl;
		    cout<<"|------------------------------------------------------|"<<endl;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->nextStudent;
    }
	cout<<"|------------------------------------------|"<<endl;
    cout << "| Student with ID " << id << " not found.   |" << endl;
    cout<<"|------------------------------------------|"<<endl;
}
void deleteCouById() {
	cout << endl;
    cout << "+---------------------------------------------------+" << endl;
    cout << "|              Delete course by course number       |" << endl;
    cout << "+---------------------------------------------------+" << endl;
	int id;
	cout << "Enter the course number of a course " << endl;
	cin >> id;
	
    if (headCourse == NULL) {
        cout<<"|-------------------------------------------------|"<<endl;
	    cout << "| Course Number with ID " << id << " Not Found.    |" << endl;
	    cout<<"|-------------------------------------------------|"<<endl;
        return;
    }
    if (headCourse->courseNo == id) {
        Course* temp = headCourse;
        headCourse = headCourse->nextCourse;
        delete temp;
        cout<<"|-----------------------------------------------------------|"<<endl;
	    cout << "| Course Number with ID " << id << " Deleted Successfully.    |" << endl;
	    cout<<"|-----------------------------------------------------------|"<<endl;
        return;
    }
    Course* prev = headCourse;
    Course* curr = headCourse->nextCourse;
    while (curr != NULL) {
        if (curr->courseNo == id) {
            prev->nextCourse = curr->nextCourse;
            delete curr;
            cout<<"|-----------------------------------------------------------|"<<endl;
		    cout << "| Course Number with ID " << id << " Deleted Successfully.    |" << endl;
		    cout<<"|-----------------------------------------------------------|"<<endl;
		    return;
        }
        	prev = curr;
        	curr = curr->nextCourse;
}
    	cout<<"|-------------------------------------------------|"<<endl;
	    cout << "| Course Number with ID " << id << " Not Found.    |" << endl;
	    cout<<"|-------------------------------------------------|"<<endl;
}

void updateCourseGrade() {
	cout << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "|          Adding Grade for student course         |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    int studentId, courseNo;
    string grade;
    cout << "Enter the Id of a student: ";
    while (!(cin >> studentId) || studentId < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    cout << "Enter the courseNo of a Course: ";
    while (!(cin >> courseNo) || courseNo < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    cout << "Enter the Grade of a Course: ";
    cin>>grade;
	// find the student
	Student *currentStudent = headStudent;
	while (currentStudent != NULL && currentStudent->id != studentId) {
	currentStudent = currentStudent->nextStudent;
	}
	if (currentStudent == NULL) {
		cout<<"|----------------------|"<<endl;
	    cout << "| Student Not Found.    |" << endl;
	    cout<<"|----------------------|"<<endl;
	return;
	}
	// find the course
	Course *currentCourse = currentStudent->courses;
	while (currentCourse != NULL && currentCourse->courseNo != courseNo) {
	    currentCourse = currentCourse->nextCourse;
	}
	if (currentCourse == NULL) {
	    cout<<"|----------------------|"<<endl;
	    cout << "| Course Not Found.    |" << endl;
	    cout<<"|----------------------|"<<endl;
	    return;
	}
	
	// update the grade
	currentCourse->grade = grade;
	
	// display the updated grade
	cout<<"+-----------------------------------------------------------------------------------------------------------------+"<<endl;
	cout <<"++"<< "Grade for course " << currentCourse->courseNo << " of student " << currentStudent->id << " is updated to:  "<<"++"<<endl;
	cout << "|    ----=="<<currentCourse->grade<< "----------------------------------------------------------------------++++||"<<endl;
	printFooter();
}
int main(int argc, char** argv) {
    int choice;
    while(true){
        clearScreen();
        printHeader();
	    cout << "+------------------------+" << endl;
	    cout << "|       Sub-Menu         |" << endl;
	    cout << "+------------------------+" << endl;
	    cout << "| 1. Register a student  |" << endl;
	    cout << "| 2. Register a course   |" << endl;
	    cout << "| 3. Register a student  |" << endl;
	    cout << "|    for a course        |" << endl;
	    cout << "| 4. Display a student   |" << endl;
	    cout << "| 5. Display a course    |" << endl;
	    cout << "| 6. Display all students|" << endl;
	    cout << "| 7. Delete student by ID|" << endl;
	    cout << "| 8. Delete course by    |" << endl;
	    cout << "|    course number       |" << endl;
	    cout << "| 9. Sort And Display    |" << endl;
	    cout << "|    Students            |" << endl;
	    cout << "| 10. Add Grade 		  |" << endl;
	    cout << "| 11. Exit               |" << endl;
	    cout << "+------------------------+" << endl;
        cout << endl << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                registerStudent();
                break;
            case 2:
                registerCourse();
                break;
            case 3:
                registerStudentForAcourse();
                break;
            case 4: 
                displayStudent();
                break;
            case 5:
                displayCourse();
                break;
            case 6:
                displayStudents();
                break;
            case 7:
                deleteStuById();
                break;
            case 8:
                deleteCouById();
                break;
            case 9:
                sortStudents();
                break;
            case 10:
                updateCourseGrade();
                break;
			case 11:
                exit(1);       
        }
        cin.ignore();
        cout << "Press Enter to continue...";
        cin.get();
    }
    return 0;
}
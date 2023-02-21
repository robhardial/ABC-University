#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype> 

using namespace std;

struct Course {
	string courseNumber;
	string courseName;
	vector<string> preReqs;
	Course() {
		courseNumber = "noCourse";
	}
};

void displayCourse(Course course) {//display course information
	cout << course.courseNumber << "|" << course.courseName << endl;
    cout << "Prerequisites: ";
	if (course.preReqs.size() > 1) {
        for (size_t i = 0; i < course.preReqs.size(); ++i) {
            cout << course.preReqs[i];
            if (i < course.preReqs.size() - 1) {
                cout << ", ";
            }
        }
    }
    else if (course.preReqs.size() == 0) {
        cout << "None";
    }
    else if (course.preReqs.size() == 1) {
        cout << course.preReqs[0] ;
    }
	cout << endl;
}

bool is_number(const std::string& s) {//checks if string is a number
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool compareCourses(const Course course1, const Course course2) {//compares courses
    return course1.courseNumber < course2.courseNumber;
 }

Course searchCourse(vector<Course> courses, string courseNum) {//searches vector for course number
    for (int i = 0; i < courses.size(); ++i) {
        if (courses.at(i).courseNumber == courseNum) {
            return courses.at(i);
            break;
        }
    }
    return {};
}

vector<Course> loadCourses(string csvPath) {//loads course objects into vector
    cout << "Loading txt file: " << csvPath << endl;

    vector<Course> courses;
    try {
        ifstream file(csvPath);
        if (!file.is_open()) {
            throw runtime_error("Error: File not found");
        }

        string line;
        while (getline(file, line)) {
            Course course;

            stringstream ss(line);
            string field;
            if (!getline(ss, field, ',')) {
                cerr << "Error: Invalid input (missing course number)" << endl;
                continue;
            }
            course.courseNumber = field;

            if (!getline(ss, field, ',')) {
                cerr << "Error: Invalid input (missing course name)" << endl;
                continue;
            }
            course.courseName = field;

            while (getline(ss, field, ',')) {
                course.preReqs.push_back(field);
            }

            courses.push_back(course);
        }

        file.close();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        courses.clear();
    }
        
        return courses;
        
}
int main() {

    vector<Course> courses;
    string fileName;

    int choice = 0;
    string input;
    bool is_valid_choice = true;
   
    while (choice != 9) {
        cout << "Welcome to Course Planner." << endl << endl;
        cout << "Menu:" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        
        
        cout << "Enter choice: ";
        cin >> input;

        if (is_number(input)) {
            choice = stoi(input);
            is_valid_choice = true;
        }
        else {
            is_valid_choice = false;
        }

        // handle invalid choice
        if (!is_valid_choice) {
            cout << "Invalid choice. Please enter a number: 1,2,3 or 9." << endl;
            continue; // repeat loop to get valid input

        }

        string courseNum;
        Course search;
        
        switch (choice) {

        case 1://load courses
            cout << "Enter file name: ";
            cin >> fileName;


            courses = loadCourses(fileName);
            if (courses.size() == 0) {
                break;
            }
            else {
                cout << "Successfully loaded";
            }
            cout << endl;
            break;

        case 2://display all courses
            cout << "Here is a sample schedule:" << endl << endl;
            sort(courses.begin(),courses.end(),compareCourses);
            for (int i = 0; i < courses.size(); ++i) {
                cout << courses.at(i).courseNumber << "|" << courses.at(i).courseName << endl;
            }
            cout << endl;
            break;

        case 3://display course
            cout << "Enter course number: ";
            cin >> courseNum;
            cout << endl;
            search = searchCourse(courses, courseNum);

            if (search.courseNumber == "noCourse") {
                cout << "Course not found" << endl;
            }
            else {
                displayCourse(search);
            }
            
            break;

        case 9://exit

            cout << endl << "Thank you for using course planner!" << endl;
            break;

        default://error
            cout << "Invalid choice Try again" << endl;
            break;

        }
        cout << endl;
    }
  

}
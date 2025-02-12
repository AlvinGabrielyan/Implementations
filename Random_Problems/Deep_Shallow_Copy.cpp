#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    vector<int> grades;

    Student(string name, vector<int> grades) {
        this->name = name;
        this->grades = grades;
    }
};

int main() {
    
    vector<int> student_grades = {85, 90, 78};
    Student student1("Alice", student_grades);

    Student deepcopy_student = student1;
    deepcopy_student.grades.push_back(95);
    
    cout << "Deep Copy Grades: ";
    for (int grade : deepcopy_student.grades) {
        cout << grade << " ";
    }
    cout << endl << "Original Grades: ";
    for (int grade : student1.grades) {
        cout << grade << " ";
    }
    cout << endl;

    Student* shallowcopy_student = &student1;
    shallowcopy_student->grades.push_back(100);
    
    cout << "Shallow Copy Grades: ";
    for (int grade : shallowcopy_student->grades) {
        cout << grade << " ";
    }
    cout << endl << "Original Grades: ";
    for (int grade : student1.grades) {
        cout << grade << " ";
    }
    cout << endl;

    return 0;
}

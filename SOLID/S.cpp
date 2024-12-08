// Single Responsibility Principle
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    int id;
public:
    Employee(const string& name, int id) : name(name), id(id) {}
    string getName() const { return name; }
    int getId() const { return id; }
};

class SalaryCalculator {
public:
    static double calculateSalary(int hoursWorked, double hourlyRate) {
        return hoursWorked * hourlyRate;
    }
};

class WorkHoursTracker {
private:
    int hoursWorked;
public:
    WorkHoursTracker() : hoursWorked(0) {}
    void logHours(int hours) { hoursWorked += hours; }
    int getHoursWorked() const { return hoursWorked; }
};

class EmployeeDisplay {
public:
    static void displayEmployeeDetails(const Employee& emp, double salary) {
        cout << emp.getName() << " (ID: " << emp.getId() << ") has a salary of: $" 
             << salary << endl;
    }
};

int main() {
    Employee emp("Alvina", 101);
    WorkHoursTracker tracker;
    tracker.logHours(40); 

    double salary = SalaryCalculator::calculateSalary(tracker.getHoursWorked(), 15.0);
    EmployeeDisplay::displayEmployeeDetails(emp, salary);

    return 0;
}

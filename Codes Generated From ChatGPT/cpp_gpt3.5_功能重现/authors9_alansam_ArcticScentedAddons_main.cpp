#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Employee base class
class Employee {
protected:
    string firstName;
    string lastName;
    double salary;
public:
    Employee(string fname, string lname, double sal) : firstName(fname), lastName(lname), salary(sal) {}
    virtual void printPaycheck() = 0; // pure virtual function
};

// Hourly employee class, derived from Employee class
class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    double hoursWorked;
public:
    HourlyEmployee(string fname, string lname, double rate, double hours) : Employee(fname, lname, 0), hourlyRate(rate), hoursWorked(hours) {}
    virtual void printPaycheck() {
        double paycheck = hourlyRate * hoursWorked;
        salary = paycheck; // update salary
        cout << "Hourly Employee: " << firstName << " " << lastName << endl;
        cout << "Paycheck: $" << paycheck << endl;
    }
};

// Salaried employee class, derived from Employee class
class SalariedEmployee : public Employee {
private:
    double bonus;
public:
    SalariedEmployee(string fname, string lname, double sal, double b) : Employee(fname, lname, sal), bonus(b) {}
    virtual void printPaycheck() {
        double paycheck = salary + bonus;
        cout << "Salaried Employee: " << firstName << " " << lastName << endl;
        cout << "Paycheck: $" << paycheck << endl;
    }
};

// Function to create an employee object based on user input
Employee* createEmployee() {
    string fname, lname;
    double salary;

    cout << "Enter employee's first name: ";
    cin >> fname;
    cout << "Enter employee's last name: ";
    cin >> lname;
    cout << "Enter employee's salary: ";
    cin >> salary;

    char type;
    cout << "Is the employee paid hourly (h) or monthly (m)? ";
    cin >> type;

    if (type == 'h') {
        double rate, hours;
        cout << "Enter hourly rate: ";
        cin >> rate;
        cout << "Enter hours worked: ";
        cin >> hours;
        return new HourlyEmployee(fname, lname, rate, hours);
    } else {
        double bonus;
        cout << "Enter bonus: ";
        cin >> bonus;
        return new SalariedEmployee(fname, lname, salary, bonus);
    }
}

// Function to load sample data and create employee objects
vector<Employee*> loadEmployees() {
    vector<Employee*> employees;
    employees.push_back(new HourlyEmployee("John", "Doe", 10.5, 40));
    employees.push_back(new SalariedEmployee("Jane", "Smith", 50000, 1000));
    return employees;
}

// Function to print the payroll report
void printPayrollReport(vector<Employee*>& employees) {
    cout << "Payroll Report" << endl;
    cout << "--------------" << endl;

    for (int i = 0; i < employees.size(); i++) {
        employees[i]->printPaycheck();
        cout << endl;
    }
}

// Function to clean up and delete employee objects
void cleanUp(vector<Employee*>& employees) {
    for (int i =0; i < employees.size(); i++) {
    delete employees[i];
    }
    }

int main() {
    char mode;
    cout << "Enter 'i' for interactive mode or 'd' for discrete mode: ";
    cin >> mode;
    vector<Employee*> employees;

    if (mode == 'i') {
        int numEmployees;
        cout << "Enter number of employees: ";
        cin >> numEmployees;

        for (int i = 0; i < numEmployees; i++) {
            Employee* emp = createEmployee();
            employees.push_back(emp);
        }
    } else {
        employees = loadEmployees();
    }

    printPayrollReport(employees);
    cleanUp(employees);

    return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Student class
class Student {
private:
    string name;
    string regNumber;
    vector<double> grades;

public:
    // Constructor
    Student(string n, string reg) {
        name = n;
        regNumber = reg;
    }

    // Add a grade
    void addGrade(double grade) {
        grades.push_back(grade);
    }

    // Calculate average
    double calculateAverage() const {
        if (grades.empty()) {
            return 0.0;
        }

        double total = 0;

        for (double grade : grades) {
            total += grade;
        }

        return total / grades.size();
    }

    // Display student information
    void display() const {
        cout << "\nName: " << name << endl;
        cout << "Registration Number: " << regNumber << endl;

        cout << "Grades: ";

        for (double grade : grades) {
            cout << grade << " ";
        }

        cout << "\nAverage: "
             << fixed << setprecision(2)
             << calculateAverage() << endl;

        if (!grades.empty()) {
            if (calculateAverage() >= 50) {
                cout << "Status: PASS" << endl;
            } else {
                cout << "Status: FAIL" << endl;
            }
        } else {
            cout << "Status: No grades entered" << endl;
        }
    }

    // Get registration number
    string getRegNumber() const {
        return regNumber;
    }

    // Add student grades
    void inputGrades() {
        int number;
        double grade;

        cout << "How many grades do you want to enter? ";
        cin >> number;

        if (cin.fail() || number <= 0 || number > 100) {
            cout << "Invalid number of grades.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (int i = 0; i < number; i++) {
            cout << "Enter grade " << i + 1 << " (0-100): ";
            cin >> grade;

            if (cin.fail() || grade < 0 || grade > 100) {
                cout << "Invalid grade. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i--;
                continue;
            }

            addGrade(grade);
        }

        cout << "Grades added successfully!\n";
    }
};

// Main application
int main() {

    vector<Student> students;
    int choice;

    do {
        cout << "\n===== STUDENT GRADE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Enter Student Grades\n";
        cout << "3. Display All Students\n";
        cout << "4. Search Student\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            case 1: {
                string name, reg;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter student name: ";
                getline(cin, name);

                cout << "Enter registration number: ";
                getline(cin, reg);

                bool exists = false;

                for (const Student& s : students) {
                    if (s.getRegNumber() == reg) {
                        exists = true;
                        break;
                    }
                }

                if (name.empty() || reg.empty()) {
                    cout << "Name and registration number cannot be empty.\n";
                } else if (exists) {
                    cout << "Student already exists!\n";
                } else {
                    students.emplace_back(name, reg);
                    cout << "Student added successfully!\n";
                }

                break;
            }

            case 2: {
                string reg;
                bool found = false;

                cout << "Enter registration number: ";
                cin >> reg;

                for (Student& s : students) {
                    if (s.getRegNumber() == reg) {
                        s.inputGrades();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Student not found!\n";
                }

                break;
            }

            case 3: {
                if (students.empty()) {
                    cout << "No students available.\n";
                } else {
                    for (const Student& s : students) {
                        s.display();
                        cout << "-------------------------\n";
                    }
                }

                break;
            }

            case 4: {
                string reg;
                bool found = false;

                cout << "Enter registration number: ";
                cin >> reg;

                for (const Student& s : students) {
                    if (s.getRegNumber() == reg) {
                        s.display();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Student not found!\n";
                }

                break;
            }

            case 5:
                cout << "Exiting application. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
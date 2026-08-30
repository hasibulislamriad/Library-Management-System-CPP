#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Student {
public:
    int id;
    string name, department, phone;
    double marks;

    Student() : id(0), marks(0) {}
    Student(int id, const string& name, const string& department,
            const string& phone, double marks)
        : id(id), name(name), department(department), phone(phone), marks(marks) {}

    double average() const { return marks; }

    string grade() const {
        if (marks >= 80) return "A+";
        if (marks >= 70) return "A";
        if (marks >= 60) return "A-";
        if (marks >= 50) return "B";
        if (marks >= 40) return "C";
        if (marks >= 33) return "D";
        return "F";
    }
};

class StudentManagementSystem {
private:
    vector<Student> students;
    const string filename = "students.txt";

    bool idExists(int id) const {
        for (const auto& s : students) if (s.id == id) return true;
        return false;
    }

public:
    StudentManagementSystem() { load(); }

    void load() {
        students.clear();
        ifstream file(filename);
        if (!file) return;

        Student s;
        while (file >> s.id) {
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(file, s.name);
            getline(file, s.department);
            getline(file, s.phone);
            file >> s.marks;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            students.push_back(s);
        }
    }

    void save() const {
        ofstream file(filename);
        for (const auto& s : students) {
            file << s.id << '\n'
                 << s.name << '\n'
                 << s.department << '\n'
                 << s.phone << '\n'
                 << s.marks << '\n';
        }
    }

    void addStudent() {
        int id;
        double marks;
        string name, department, phone;

        cout << "\n========== ADD STUDENT ==========\nID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idExists(id)) {
            cout << "Student ID already exists!\n";
            return;
        }

        cout << "Name: "; getline(cin, name);
        cout << "Department: "; getline(cin, department);
        cout << "Phone: "; getline(cin, phone);
        cout << "Average Marks (0-100): "; cin >> marks;

        if (marks < 0 || marks > 100) {
            cout << "Marks must be between 0 and 100.\n";
            return;
        }

        students.emplace_back(id, name, department, phone, marks);
        save();
        cout << "Student added successfully!\n";
    }

    void showAll() const {
        cout << "\n============================== ALL STUDENTS ==============================\n";
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        cout << left << setw(8) << "ID" << setw(24) << "Name"
             << setw(18) << "Department" << setw(18) << "Phone"
             << setw(10) << "Marks" << "Grade\n";
        cout << string(96, '-') << '\n';

        for (const auto& s : students) {
            cout << left << setw(8) << s.id << setw(24) << s.name
                 << setw(18) << s.department << setw(18) << s.phone
                 << setw(10) << fixed << setprecision(2) << s.marks
                 << s.grade() << '\n';
        }
    }

    void searchStudent() const {
        int id;
        cout << "\n========== SEARCH STUDENT ==========\nID: ";
        cin >> id;

        for (const auto& s : students) {
            if (s.id == id) {
                cout << "\nStudent Found!\n-----------------------------\n"
                     << "ID         : " << s.id << '\n'
                     << "Name       : " << s.name << '\n'
                     << "Department : " << s.department << '\n'
                     << "Phone      : " << s.phone << '\n'
                     << "Marks      : " << fixed << setprecision(2) << s.marks << '\n'
                     << "Grade      : " << s.grade() << '\n';
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void updateStudent() {
        int id;
        cout << "\n========== UPDATE STUDENT ==========\nID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (auto& s : students) {
            if (s.id == id) {
                cout << "New Name: "; getline(cin, s.name);
                cout << "New Department: "; getline(cin, s.department);
                cout << "New Phone: "; getline(cin, s.phone);
                cout << "New Average Marks (0-100): "; cin >> s.marks;

                if (s.marks < 0 || s.marks > 100) {
                    cout << "Invalid marks. Update cancelled.\n";
                    return;
                }

                save();
                cout << "Student updated successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void deleteStudent() {
        int id;
        cout << "\n========== DELETE STUDENT ==========\nID: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                save();
                cout << "Student deleted successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void statistics() const {
        if (students.empty()) {
            cout << "\nNo student data available.\n";
            return;
        }

        double total = 0;
        int passed = 0, failed = 0;
        double highest = students.front().marks;
        double lowest = students.front().marks;

        for (const auto& s : students) {
            total += s.marks;
            if (s.marks >= 33) ++passed;
            else ++failed;
            highest = max(highest, s.marks);
            lowest = min(lowest, s.marks);
        }

        cout << "\n========== STUDENT STATISTICS ==========\n"
             << "Total Students : " << students.size() << '\n'
             << "Passed         : " << passed << '\n'
             << "Failed         : " << failed << '\n'
             << "Class Average  : " << fixed << setprecision(2) << total / students.size() << '\n'
             << "Highest Marks  : " << highest << '\n'
             << "Lowest Marks   : " << lowest << '\n';
    }
};

int main() {
    StudentManagementSystem sms;
    int choice;

    while (true) {
        cout << "\n=============================================\n"
             << "       STUDENT MANAGEMENT SYSTEM\n"
             << "=============================================\n"
             << "1. Add Student\n"
             << "2. Show All Students\n"
             << "3. Search Student\n"
             << "4. Update Student\n"
             << "5. Delete Student\n"
             << "6. Student Statistics\n"
             << "7. Exit\n"
             << "=============================================\n"
             << "Choice: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: sms.addStudent(); break;
            case 2: sms.showAll(); break;
            case 3: sms.searchStudent(); break;
            case 4: sms.updateStudent(); break;
            case 5: sms.deleteStudent(); break;
            case 6: sms.statistics(); break;
            case 7: cout << "Thank you!\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Student {
public:
    string name;
    long id;
    vector<int> grades;

    void addstud(const string& n, long id1) {
        name = n;
        id = id1;
    }

    void addgrades(int gradeCount) {
        grades.clear();
        cout << "Enter " << gradeCount << " grades for " << name << ":\n";
        for (int i = 0; i < gradeCount; ++i) {
            int g;
            cout << "Grade " << i + 1 << ": ";
            cin >> g;
            grades.push_back(g);
        }
        cout << "Grades added successfully!\n";
    }

    void display() const {
        cout << "\nName: " << name << "\nID: " << id << "\nGrades: ";
        if (grades.empty()) {cout << "No grades entered!";}
        else
        { for (int i=0;i<grades.size();i++)
        { cout << grades[i] << " ";}
        cout << endl;}
    }

    void average() const {
        if (grades.empty()) {
            cout << "No grades entered for " << name << endl;
            return;
        }
        float sum = 0;
        for (int i=0;i<grades.size();i++)
         sum += grades[i];
        cout << "Average marks of " << name << " (ID: " << id << ") = "
             << sum / grades.size() << endl;
    }
};


void saveToFile(const vector<Student>& s, int gradeCount) {
    ofstream out("students.txt");
    if (!out) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }
    out << gradeCount << "\n"; 
    for (int i=0;i<s.size();++i) {
        out << s[i].name << " " << s[i].id;
        for (int j=0;j<s[i].grades.size();++j)
         out << " " << s[i].grades[j];
        out << "\n";
    }
    out.close();
    cout << "\n? Data saved successfully to file.\n";
}


vector<Student> loadFromFile(int& gradeCount) {
    vector<Student> s;
    ifstream in("students.txt");
    if (!in) {
        cout << "No saved data found. Starting fresh.\n";
        gradeCount = 0;
        return s;
    }

    in >> gradeCount;
    Student temp;
    while (in >> temp.name >> temp.id) {
        temp.grades.clear();
        for (int i = 0; i < gradeCount; ++i) {
            int g;
            if (!(in >> g)) break;
            temp.grades.push_back(g);
        }
        s.push_back(temp);
    }
    in.close();
    cout << "? Loaded " << s.size() << " student(s) from file.\n";
    return s;
}

int main() {
    int gradeCount = 0;
    vector<Student> s = loadFromFile(gradeCount);

    int ch;
    string n;
    long id;
    int index;

    while (true) {
        cout << "\n========= STUDENT GRADE BOOK =========";
        cout << "\n1. Add Student";
        cout << "\n2. Add Grades";
        cout << "\n3. Display Grades";
        cout << "\n4. Show Average";
        cout << "\n5. Exit and Save";
        cout << "\n======================================";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1: {
            Student temp;
            cout << "Enter student name: ";
            cin >> n;
            cout << "Enter student ID: ";
            cin >> id;
            temp.addstud(n, id);
            s.push_back(temp);
            cout << "Student added successfully!\n";
            break;
        }

        case 2: {
            if (s.empty()) { cout << "No students available! Add students first.\n"; break; }
            if (gradeCount == 0) {
                cout << "Enter how many grades each student will have: ";
                cin >> gradeCount;
            }

            cout << "Enter student number (0 - " << s.size() - 1 << "): ";
            cin >> index;
            if (index < 0 || index >= s.size()) { cout << "Invalid student number!\n"; break; }

            s[index].addgrades(gradeCount);
            break;
        }

        case 3: {
            if (s.empty()) { cout << "No students to display!\n"; break; }
            cout << "Enter student number (0 - " << s.size() - 1 << "): ";
            cin >> index;
            if (index < 0 || index >= s.size()) { cout << "Invalid student number!\n"; break; }
            s[index].display();
            break;
        }

        case 4: {
            if (s.empty()) { cout << "No students to calculate average!\n"; break; }
            cout << "Enter student number (0 - " << s.size() - 1 << "): ";
            cin >> index;
            if (index < 0 || index >= s.size()) { cout << "Invalid student number!\n"; break; }
            s[index].average();
            break;
        }

        case 5:
            saveToFile(s, gradeCount);
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}

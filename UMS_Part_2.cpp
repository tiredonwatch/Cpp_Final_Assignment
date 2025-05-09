

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Person {
private:
    string name;
    int age;
    string id;
    string contactInfo;

public:
    Person() {}
    virtual ~Person() {}

    void setName(string name) {
        this->name = name;
    }

    void setAge(int age) {
        if (age > 0 && age < 120) {
            this->age = age;
        } else {
            this->age = 18; 
        }
    }

    void setId(string id) {
        this->id = id;
    }

    void setContactInfo(string contactInfo) {
        this->contactInfo = contactInfo;
    }

    string getName() { return name; }
    int getAge() { return age; }
    string getId() { return id; }
    string getContactInfo() { return contactInfo; }

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age
             << ", ID: " << id << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() {
        return 0.0; 
    }
};


class Student : public Person {
private:
    string enrollmentDate;
    vector<string> programs;
    double gpa;

public:
    Student() {}

    void setEnrollmentDate(string date) {
        enrollmentDate = date;
    }

    void addProgram(string program) {
        if (!program.empty()) {
            programs.push_back(program);
        }
    }

    void setGPA(double gpa) {
        this->gpa = (gpa >= 0.0 && gpa <= 4.0) ? gpa : 0.0;
    }

    double getGPA() { return gpa; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << ", Programs: ";
        for (int i = 0; i < programs.size(); i++) {
            cout << programs[i];
            if (i < programs.size() - 1) cout << ", ";
        }
        cout << ", GPA: " << gpa << endl;
    }

};

class Professor : public Person {
private:
    string department;
    string specialization;
    string hireDate;

public:
    Professor() {}

    void setDepartment(string dept) { department = dept; }
    void setSpecialization(string spec) { specialization = spec; }
    void setHireDate(string date) { hireDate = date; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << department
             << ", Specialization: " << specialization
             << ", Hire Date: " << hireDate << endl;
    }

    double calculatePayment() override {
        return 5000.0; 
    }
};


class Course {
private:
    string code;
    string title;
    int credits;
    string description;

public:
    Course(string code, string title, int credits, string description) {
        this->code = code;
        this->title = title;
        setCredits(credits);
        this->description = description;
    }

    void setCredits(int credits) {
        this->credits = (credits > 0) ? credits : 3;
    }

    int getCredits() { return credits; }
};


class Department {
private:
    string name;
    string location;
    double budget;

public:
    Department(string name, string location, double budget) {
        this->name = name;
        this->location = location;
        this->budget = budget;
    }
};

class GradeBook {
private:
    vector<string> studentIds;
    vector<double> studentGrades;

public:
    void addGrade(string studentId, double grade) {
        studentIds.push_back(studentId);
        studentGrades.push_back(grade);
    }

    double calculateAverageGrade() {
        if (studentGrades.empty()) return 0.0;
        double total = 0;
        for (int i = 0; i < studentGrades.size(); i++) {
            total += studentGrades[i];
        }
        return total / studentGrades.size();
    }

    double getHighestGrade() {
        double maxGrade = 0;
        for (int i = 0; i < studentGrades.size(); i++) {
            if (studentGrades[i] > maxGrade) {
                maxGrade = studentGrades[i];
            }
        }
        return maxGrade;
    }

    void getFailingStudents() {
        cout << "Failing Students (grade < 60):" << endl;
        for (int i = 0; i < studentGrades.size(); i++) {
            if (studentGrades[i] < 60) {
                cout << "Student ID: " << studentIds[i] << ", Grade: " << studentGrades[i] << endl;
            }
        }
    }
};

class EnrollmentManager {
private:
    vector<string> studentIds;
    vector<string> courseCodes;

public:
    void enrollStudent(string studentId, string courseCode) {
        studentIds.push_back(studentId);
        courseCodes.push_back(courseCode);
    }

    void dropStudent(string studentId, string courseCode) {
        for (int i = 0; i < studentIds.size(); i++) {
            if (studentIds[i] == studentId && courseCodes[i] == courseCode) {
                studentIds.erase(studentIds.begin() + i);
                courseCodes.erase(courseCodes.begin() + i);
                break;
            }
        }
    }

    int getEnrollmentCount(string courseCode) {
        int count = 0;
        for (int i = 0; i < courseCodes.size(); i++) {
            if (courseCodes[i] == courseCode) {
                count++;
            }
        }
        return count;
    }
};

void testPolymorphism(Person* person) {
    person->displayDetails();

    Professor* prof = dynamic_cast<Professor*>(person);
    if (prof != nullptr) {
        cout << "Payment: $" << prof->calculatePayment() << endl;
    }
}


int main() {

    vector<Person*> people;
    int choice;

    do {
        cout << "\n=== University Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. Add Professor\n";
        cout << "3. Show All People\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            Student* s = new Student();
            string name, id, contact, enrollDate;
            int age, numPrograms;
            double gpa;

            cout << "Enter student name: ";
            getline(cin, name);
            s->setName(name);

            cout << "Enter student age: ";
            cin >> age;
            s->setAge(age);

            cout << "Enter student ID: ";
            cin >> id;
            s->setId(id);

            cout << "Enter contact info: ";
            cin.ignore();
            getline(cin, contact);
            s->setContactInfo(contact);

            cout << "Enter enrollment date (e.g., 2023-09-01): ";
            getline(cin, enrollDate);
            s->setEnrollmentDate(enrollDate);

            cout << "How many programs is the student enrolled in? ";
            cin >> numPrograms;
            cin.ignore();

            for (int i = 0; i < numPrograms; i++) {
                string prog;
                cout << "Enter name of program " << (i + 1) << ": ";
                getline(cin, prog);
                s->addProgram(prog);
            }

            cout << "Enter student's GPA: ";
            cin >> gpa;
            s->setGPA(gpa);

            people.push_back(s);
            cout << "Student added!\n";

        } else if (choice == 2) {
            Professor* p = new Professor();
            string name, id, contact, dept, spec, hireDate;
            int age;

            cout << "Enter professor name: ";
            getline(cin, name);
            p->setName(name);

            cout << "Enter professor age: ";
            cin >> age;
            p->setAge(age);

            cout << "Enter professor ID: ";
            cin >> id;
            p->setId(id);

            cout << "Enter contact info: ";
            cin.ignore();
            getline(cin, contact);
            p->setContactInfo(contact);

            cout << "Enter department: ";
            getline(cin, dept);
            p->setDepartment(dept);

            cout << "Enter specialization: ";
            getline(cin, spec);
            p->setSpecialization(spec);

            cout << "Enter hire date (e.g., 2020-08-15): ";
            getline(cin, hireDate);
            p->setHireDate(hireDate);

            people.push_back(p);
            cout << "Professor added!\n";

        } else if (choice == 3) {
            cout << "\n--- Showing All Persons ---\n";
            for (int i = 0; i < people.size(); i++) {
                testPolymorphism(people[i]);
                cout << "--------------------------\n";
            }
        }

    } while (choice != 4);



    cout << "Goodbye!\n";
    return 0;
}
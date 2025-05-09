#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string id;
    string contactInfo;

public:
    Person() {}
    virtual ~Person() {}

    Person(string name, int age, string id, string contactInfo) {
        this->name = name;
        this->age = (age > 0 && age < 120) ? age : 18;
        this->id = id;
        this->contactInfo = contactInfo;
    }

    void setName(string n) { name = n; }
    void setAge(int a) { age = (a > 0 && a < 120) ? a : 18; }
    void setId(string i) { id = i; }
    void setContactInfo(string c) { contactInfo = c; }

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() {
        return 0.0;
    }
};

class Student;
class Course;
class Professor;

class Department {
private:
    string name;
    string location;
    double budget;
    vector<Professor*> professors;

public:
    Department(string name, string location, double budget)
        : name(name), location(location), budget(budget) {}

    void addProfessor(Professor* p) {
        professors.push_back(p);
    }
};

class Course {
private:
    string code;
    string title;
    int credits;
    string description;
    Professor* instructor;

public:
    Course(string code, string title, int credits, string description, Professor* instructor)
        : code(code), title(title), credits(credits > 0 ? credits : 3), description(description), instructor(instructor) {}
};

class Student : public Person {
protected:
    string enrollmentDate;
    vector<string> programs;
    double gpa;
    vector<Course*> courses;

public:
    Student() {}
    Student(string name, int age, string id, string contactInfo, string enrollmentDate, double gpa)
        : Person(name, age, id, contactInfo), enrollmentDate(enrollmentDate), gpa(gpa) {}

    void addProgram(string program) {
        if (!program.empty()) {
            programs.push_back(program);
        }
    }

    void enrollInCourse(Course* course) {
        courses.push_back(course);
    }

    double getGPA() { return gpa; }

    void setEnrollmentDate(string date) { enrollmentDate = date; }
    void setGPA(double g) { gpa = g; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << ", Programs: ";
        for (int i = 0; i < programs.size(); i++) {
            cout << programs[i];
            if (i < programs.size() - 1) cout << ", ";
        }
        cout << ", GPA: " << gpa << endl;
    }

    double calculatePayment() override {
        return 2000.0;
    }
};

class UndergraduateStudent : public Student {
private:
    string major;
    string minor;
    string expectedGraduationDate;

public:
    UndergraduateStudent(string name, int age, string id, string contactInfo, string enrollmentDate, double gpa,
                         string major, string minor, string gradDate)
        : Student(name, age, id, contactInfo, enrollmentDate, gpa), major(major), minor(minor), expectedGraduationDate(gradDate) {}

    void displayDetails() override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor << ", Expected Graduation: " << expectedGraduationDate << endl;
    }
};

class GraduateStudent : public Student {
private:
    string researchTopic;
    Professor* advisor;
    string thesisTitle;
    vector<string> assistantships;

public:
    GraduateStudent(string name, int age, string id, string contactInfo, string enrollmentDate, double gpa,
                    string researchTopic, Professor* advisor, string thesisTitle)
        : Student(name, age, id, contactInfo, enrollmentDate, gpa),
          researchTopic(researchTopic), advisor(advisor), thesisTitle(thesisTitle) {}

    void displayDetails() override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << ", Thesis Title: " << thesisTitle << endl;
        if (!assistantships.empty()) {
            cout << "Assistantships: ";
            for (int i = 0; i < assistantships.size(); i++) {
                cout << assistantships[i];
                if (i < assistantships.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }

    void addAssistantship(string type) {
        if (!type.empty()) {
            assistantships.push_back(type);
            cout << "Assistantship assigned: " << type << endl;
        }
    }
};

class Professor : public Person {
protected:
    string department;
    string specialization;
    string hireDate;
    int yearsOfService;
    double baseSalary;

public:
    Professor() {}
    Professor(string name, int age, string id, string contactInfo, string department, string specialization, string hireDate, int yearsOfService, double baseSalary)
        : Person(name, age, id, contactInfo), department(department), specialization(specialization), hireDate(hireDate), yearsOfService(yearsOfService), baseSalary(baseSalary) {}

    void setDepartment(string dept) { department = dept; }
    void setSpecialization(string spec) { specialization = spec; }
    void setHireDate(string date) { hireDate = date; }

    virtual void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << ", Years of Service: " << yearsOfService << ", Base Salary: " << baseSalary << endl;
    }
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string name, int age, string id, string contactInfo, string department, string specialization, string hireDate, int yearsOfService, double baseSalary)
        : Professor(name, age, id, contactInfo, department, specialization, hireDate, yearsOfService, baseSalary) {}

    double calculatePayment() override {
        return baseSalary + 200 * yearsOfService;
    }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string name, int age, string id, string contactInfo, string department, string specialization, string hireDate, int yearsOfService, double baseSalary)
        : Professor(name, age, id, contactInfo, department, specialization, hireDate, yearsOfService, baseSalary) {}

    double calculatePayment() override {
        return baseSalary + 300 * yearsOfService;
    }
};

class FullProfessor : public Professor {
private:
    double researchGrant;

public:
    FullProfessor(string name, int age, string id, string contactInfo, string department, string specialization, string hireDate, int yearsOfService, double baseSalary, double researchGrant)
        : Professor(name, age, id, contactInfo, department, specialization, hireDate, yearsOfService, baseSalary), researchGrant(researchGrant) {}

    double calculatePayment() override {
        return baseSalary + 500 * yearsOfService + researchGrant;
    }

    void displayDetails() override {
        Professor::displayDetails();
        cout << "Research Grant: " << researchGrant << endl;
    }
};

class Classroom {
private:
    string building;
    int roomNumber;

public:
    Classroom(string building, int roomNumber) : building(building), roomNumber(roomNumber) {}
};

class Schedule {
private:
    vector<string> timeSlots;

public:
    void addTimeSlot(string slot) {
        timeSlots.push_back(slot);
    }
};

class University {
private:
    vector<Department*> departments;

public:
    void addDepartment(Department* dept) {
        departments.push_back(dept);
    }
};

void testPolymorphism(Person* p) {
    p->displayDetails();
    cout << "Calculated Payment: $" << p->calculatePayment() << endl;
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

}

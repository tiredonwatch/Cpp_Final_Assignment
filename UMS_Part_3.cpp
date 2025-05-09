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
    vector<Student*> students;
    vector<Course*> courses;
public:
    Department(string name, string location, double budget)
        : name(name), location(location), budget(budget) {}

    void addProfessor(Professor* p) {
        professors.push_back(p);
    }

    void addStudent(Student* s) {
        students.push_back(s);
    }

    void addCourse(Course* c) {
        courses.push_back(c);
    }

    void displaySummary() {
        cout << "Department: " << name << ", Professors: " << professors.size() << ", Students: " << students.size() << ", Courses: " << courses.size() << endl;
    }
};

class Course {
private:
    string code;
    string title;
    int credits;
    string description;
    Professor* instructor;
    vector<Student*> enrolledStudents;

public:
    Course(string code, string title, int credits, string description, Professor* instructor)
        : code(code), title(title), credits(credits > 0 ? credits : 3), description(description), instructor(instructor) {}

    void addStudent(Student* s) {
        enrolledStudents.push_back(s);
    }

    void displayEnrolledStudents() {
        cout << "Course: " << title << " has " << enrolledStudents.size() << " enrolled students." << endl;
    }
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
        course->addStudent(this);
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
        return gpa > 3.7 ? 1000.0 : 2000.0;
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
    bool thesisApproved = false;

public:
    GraduateStudent(string name, int age, string id, string contactInfo, string enrollmentDate, double gpa,
                    string researchTopic, Professor* advisor, string thesisTitle)
        : Student(name, age, id, contactInfo, enrollmentDate, gpa),
          researchTopic(researchTopic), advisor(advisor), thesisTitle(thesisTitle) {}

    void displayDetails() override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << ", Thesis Title: " << thesisTitle;
        cout << ", Thesis Approved: " << (thesisApproved ? "Yes" : "No") << endl;
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

    void approveThesis() {
        thesisApproved = true;
        cout << "Thesis approved." << endl;
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
    Professor() : Person("", 0, "", ""), department(""), specialization(""), hireDate(""), yearsOfService(0), baseSalary(0.0) {}

    Professor(string name, int age, string id, string contactInfo, string department, string specialization, string hireDate, int yearsOfService, double baseSalary)
        : Person(name, age, id, contactInfo), department(department), specialization(specialization), hireDate(hireDate), yearsOfService(yearsOfService), baseSalary(baseSalary) {}

    void setDepartment(string dept) { department = dept; }
    void setSpecialization(string spec) { specialization = spec; }
    void setHireDate(string date) { hireDate = date; }

    virtual void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << ", Years of Service: " << yearsOfService << ", Base Salary: " << baseSalary << endl;
    }

    void approveThesis(GraduateStudent* student) {
        student->approveThesis();
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

    void displayDetails() {
        cout << "Classroom - Building: " << building << ", Room Number: " << roomNumber << endl;
    }
};

class Schedule {
private:
    vector<string> timeSlots;

public:
    void addTimeSlot(string slot) {
        timeSlots.push_back(slot);
    }

    void displaySchedule() {
        cout << "Schedule Time Slots: ";
        for (const string& slot : timeSlots) {
            cout << slot << ", ";
        }
        cout << endl;
    }
};

class University {
private:
    vector<Department*> departments;

public:
    void addDepartment(Department* dept) {
        departments.push_back(dept);
    }

    void displayDepartments() {
        cout << "University has " << departments.size() << " department(s)." << endl;
        for (Department* d : departments) {
            d->displaySummary();
        }
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
        cout << "1. Add Undergraduate Student\n";
        cout << "2. Add Graduate Student\n";
        cout << "3. Add Assistant Professor\n";
        cout << "4. Add Associate Professor\n";
        cout << "5. Add Full Professor\n";
        cout << "6. Show All People\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name, id, contact, enrollDate, major, minor, gradDate;
            int age;
            double gpa;

            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter contact info: ";
            getline(cin, contact);
            cout << "Enter enrollment date: ";
            getline(cin, enrollDate);
            cout << "Enter GPA: ";
            cin >> gpa;
            cin.ignore();
            cout << "Enter major: ";
            getline(cin, major);
            cout << "Enter minor: ";
            getline(cin, minor);
            cout << "Enter expected graduation date: ";
            getline(cin, gradDate);

            UndergraduateStudent* s = new UndergraduateStudent(name, age, id, contact, enrollDate, gpa, major, minor, gradDate);
            people.push_back(s);
            cout << "Undergraduate Student added!\n";
        }
        else if (choice == 2) {
            string name, id, contact, enrollDate, researchTopic, thesisTitle;
            int age;
            double gpa;

            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter contact info: ";
            getline(cin, contact);
            cout << "Enter enrollment date: ";
            getline(cin, enrollDate);
            cout << "Enter GPA: ";
            cin >> gpa;
            cin.ignore();
            cout << "Enter research topic: ";
            getline(cin, researchTopic);
            cout << "Enter thesis title: ";
            getline(cin, thesisTitle);

            GraduateStudent* s = new GraduateStudent(name, age, id, contact, enrollDate, gpa, researchTopic, nullptr, thesisTitle);
            int numAssist;
            cout << "How many assistantships? ";
            cin >> numAssist;
            cin.ignore();
            for (int i = 0; i < numAssist; i++) {
                string assist;
                cout << "Enter assistantship " << (i + 1) << ": ";
                getline(cin, assist);
                s->addAssistantship(assist);
            }
            people.push_back(s);
            cout << "Graduate Student added!\n";
        }
        else if (choice == 3 || choice == 4 || choice == 5) {
            string name, id, contact, dept, spec, hireDate;
            int age, years;
            double baseSalary;

            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter ID: ";
            getline(cin, id);
            cout << "Enter contact info: ";
            getline(cin, contact);
            cout << "Enter department: ";
            getline(cin, dept);
            cout << "Enter specialization: ";
            getline(cin, spec);
            cout << "Enter hire date: ";
            getline(cin, hireDate);
            cout << "Enter years of service: ";
            cin >> years;
            cout << "Enter base salary: ";
            cin >> baseSalary;
            cin.ignore();

            Professor* p = nullptr;
            if (choice == 3)
                p = new AssistantProfessor(name, age, id, contact, dept, spec, hireDate, years, baseSalary);
            else if (choice == 4)
                p = new AssociateProfessor(name, age, id, contact, dept, spec, hireDate, years, baseSalary);
            else {
                double grant;
                cout << "Enter research grant: ";
                cin >> grant;
                cin.ignore();
                p = new FullProfessor(name, age, id, contact, dept, spec, hireDate, years, baseSalary, grant);
            }
            people.push_back(p);
            cout << "Professor added!\n";
        }
        else if (choice == 6) {
            cout << "\n--- Showing All People ---\n";
            for (Person* p : people) {
                testPolymorphism(p);
                cout << "--------------------------\n";
            }
        }
    } while (choice != 7);

}

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:                                  
    int    rollNo;
    string name;
    float  marks;
    static int count;                      

    float validMarks(float m) const {      
        if (m < 0)   return 0;
        if (m > 100) return 100;
        return m;
    }

public:
    
    Student(int r, string n, float m) : rollNo(r), name(n), marks(validMarks(m)) {
        ++count;
        cout << "[Constructor] Student created : " << name << endl;
    }

    
    Student(const Student &s) : rollNo(s.rollNo), name(s.name), marks(s.marks) {
        ++count;
        cout << "[Copy Constructor] Copy created for : " << name << endl;
    }

    
    ~Student() {
        --count;
        cout << "[Destructor] Student removed : " << name << endl;
    }

    
    int    getRollNo() const { return rollNo; }
    string getName()   const { return name; }
    float  getMarks()  const { return marks; }

   
    void setMarks(float m) {                               
        marks = validMarks(m);
    }
    void setMarks(float m1, float m2, float m3) {          
        marks = validMarks((m1 + m2 + m3) / 3.0f);
    }

    
    void display() const {                                
        cout << left << setw(8) << rollNo << setw(12) << name
             << fixed << setprecision(2) << marks << endl;
    }
    void display(bool showResult) const {                 
        display();
        if (showResult)
            cout << "        Result : " << (marks >= 40 ? "PASS" : "FAIL") << endl;
    }

    
    static int getCount() { return count; }

    
    bool operator>(const Student &other) const {
        return marks > other.marks;
    }

   
    friend void printReport(const Student &s);
};


int Student::count = 0;


void printReport(const Student &s) {
    char grade;
    if      (s.marks >= 90) grade = 'A';
    else if (s.marks >= 75) grade = 'B';
    else if (s.marks >= 60) grade = 'C';
    else if (s.marks >= 40) grade = 'D';
    else                    grade = 'F';

    cout << "  Report Card -> Roll No: " << s.rollNo
         << " | Name: " << s.name
         << " | Marks: " << fixed << setprecision(2) << s.marks
         << " | Grade: " << grade << endl;
}

int main() {
    cout << "===== STUDENT MANAGEMENT (OOP USING C++) =====\n\n";

    cout << "--- 1. Creating students (parameterized constructor) ---\n";
    Student s1(101, "Arun", 82.5f);
    Student s2(102, "Meena", 91.0f);
    Student *s3 = new Student(103, "Karthik", 0);   
    cout << "Total students = " << Student::getCount() << "\n\n";

    cout << "--- 2. Overloaded display() ---\n";
    cout << left << setw(8) << "Roll" << setw(12) << "Name" << "Marks" << endl;
    s1.display();                
    s2.display(true);             
    s3->display(true);
    cout << endl;

    cout << "--- 3. Overloaded setMarks() ---\n";
    s3->setMarks(68.0f);                        
    cout << "After setMarks(68):            ";
    s3->display();
    s3->setMarks(70.0f, 75.0f, 80.0f);           
    cout << "After setMarks(70, 75, 80):    ";
    s3->display();
    cout << endl;

    cout << "--- 4. Operator overloading (>) ---\n";
    if (s1 > s2)
        cout << s1.getName() << " scored higher than " << s2.getName() << endl;
    else if (s2 > s1)
        cout << s2.getName() << " scored higher than " << s1.getName() << endl;
    else
        cout << s1.getName() << " and " << s2.getName() << " scored equal marks" << endl;

    if (*s3 > s1)
        cout << s3->getName() << " scored higher than " << s1.getName() << endl;
    else if (s1 > *s3)
        cout << s1.getName() << " scored higher than " << s3->getName() << endl;
    else
        cout << s1.getName() << " and " << s3->getName() << " scored equal marks" << endl;
    cout << endl;

    cout << "--- 5. Friend function printReport() ---\n";
    printReport(s1);
    printReport(s2);
    printReport(*s3);
    cout << endl;

    cout << "--- 6. Static member (student count) ---\n";
    {
        Student s4(s1);                          
        cout << "Count inside block  = " << Student::getCount() << endl;
    }                                            
    cout << "Count after block   = " << Student::getCount() << endl;

    delete s3;                                   
    cout << "Count after delete  = " << Student::getCount() << "\n\n";

    cout << "===== END OF PROGRAM =====\n";
    return 0;                                    
}
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;



// 1. BASE CLASS (Encapsulation)

class User {
protected:
    string name;
    string id;
    string password;

public:
    void setName(string n) {
        name = n; 
    }

    void setID(string ID) {
        id = ID; 
    }

    void setPassword(string pass) { 
        password = pass; 
    }
    
    string getName() { 
        return name; 
    }

    string getID() { 
        return id; 
    }

    string getPass() { 
        return password; 
    }

};



// 2. STUDENT CLASS (The Portal):

class Student : public User {
private:
    string degree;
    string batch;
    string section;

public:
    void setStudentData(string n, string i, string d, string b, string s) {
        name = n; id = i; degree = d; batch = b; section = s;
    }

    void displayHeader() {

        cout << "\n****************************************************";
        cout << "\n* FLEX STUDENT PORTAL SYSTEM           *";
        cout << "\n****************************************************";
    }


    void displayPortal() {

        displayHeader();

        cout << "\n Welcome back, " << name;
        cout << "\n --------------------------------------------------";
        cout << "\n | Roll No: " << left << setw(15) << id << " | Degree: " << degree;
        cout << "\n | Batch:   " << left << setw(15) << batch << " | Section: " << section;
        cout << "\n --------------------------------------------------\n";
    }

    void registerCourse() {
        string code, cname, credit;
        ifstream inFile("courses.txt");
        
        cout << "\n--- AVAILABLE COURSE CATALOG ---\n";
        cout << left << setw(10) << "CODE" << setw(25) << "COURSE NAME" << "CREDITS" << endl;
        cout << "----------------------------------------------------\n";
        
        while (getline(inFile, code, ',') && getline(inFile, cname, ',') && getline(inFile, credit)) {

            cout << left << setw(10) << code << setw(25) << cname << credit << endl;

        }
        inFile.close();

        string choiceCode;

        cout << "\nEnter Course Code to Register: ";
        cin >> choiceCode;

        // Validation: Prevent duplicate registration
        ifstream checkFile("registrations.txt");
        string rID, rCode;

        bool alreadyReg = false;

        while (getline(checkFile, rID, ',') && getline(checkFile, rCode)) {

            if (rID == id && rCode == choiceCode) {
                alreadyReg = true;
                break;
            }

        }

        checkFile.close();

        if (alreadyReg) {
            cout << "\n[!] ERROR: You are already registered for " << choiceCode << "!\n";
        }
        else {
            ofstream outFile("registrations.txt", ios::app);

            outFile << id << "," << choiceCode << endl;
            outFile.close();
            cout << "\n[SUCCESS] Course " << choiceCode << " registered successfully.\n";
        }

    }

    void viewAttendance() {
        string attID, attCode, status, date;
        int presents = 0, absents = 0;
        ifstream inFile("attendance.txt");
        
        cout << "\n--- DETAILED ATTENDANCE HISTORY ---\n";
        cout << left << setw(15) << "DATE" << setw(15) << "COURSE" << "STATUS" << endl;
        cout << "----------------------------------------------------\n";
        
        while (getline(inFile, attID, ',') && getline(inFile, attCode, ',') && 
               getline(inFile, status, ',') && getline(inFile, date)) {

            if (attID == id) {
                cout << left << setw(15) << date << setw(15) << attCode << (status == "P" ? "Present" : "Absent") << endl;

                if(status == "P") presents++; else absents++;
            }

        }

        inFile.close();

        
        float percentage = (presents + absents > 0) ? ((float)presents / (presents + absents)) * 100 : 0;

        cout << "----------------------------------------------------\n";
        cout << "Summary: Presents: " << presents << " | Absents: " << absents << " | Percentage: " << fixed << setprecision(2) << percentage << "%\n";
    }

    void viewTranscript() {
        string mID, mCode, mid, fin;
        ifstream inFile("marks.txt");
        
        displayHeader();

        cout << "\n                  OFFICIAL ACADEMIC TRANSCRIPT";
        cout << "\n------------------------------------------------------------";
        cout << "\n" << left << setw(15) << "COURSE" << setw(12) << "MID(30)" << setw(12) << "FINAL(50)" << setw(10) << "TOTAL" << "GRADE";
        cout << "\n------------------------------------------------------------";
        
        while (getline(inFile, mID, ',') && getline(inFile, mCode, ',') && getline(inFile, mid, ',') && getline(inFile, fin)) {

            if (mID == id) {
                float m = stof(mid);
                float f = stof(fin);
                float total = m + f;
                string grade;

                if(total >= 80) {
                    grade = "A";
                }

                else if(total >= 70) {
                    grade = "B";
                }

                else if(total >= 60) {
                    grade = "C";
                }

                else if(total >= 50) {
                    grade = "D";
                }

                else {
                    grade = "F";
                }

                
                cout << "\n" << left << setw(15) << mCode << setw(12) << mid << setw(12) << fin << setw(10) << total << grade;
            }

        }

        cout << "\n------------------------------------------------------------\n";
        inFile.close();
    }


    void viewFees() {
        string fID, amount, status;
        ifstream inFile("fees.txt");
        bool found = false;
        
        cout << "\n--- UNIVERSITY FEE STATUS ---\n";

        while (getline(inFile, fID, ',') && getline(inFile, amount, ',') && getline(inFile, status)) {

            if (fID == id) {
                cout << "Student ID:     " << fID << endl;
                cout << "Total Amount:   Rs. " << amount << endl;
                cout << "Payment Status: " << status << endl;
                found = true;
            }

        }

        if(!found) cout << "No fee records generated for current session.\n";
        inFile.close();

    }


    void studentMenu() {
        int choice;

        while(true) {
            cout << "\n--- STUDENT SIDEBAR MENU ---\n";
            cout << "1. View Home Profile\n2. Register New Course\n3. View Attendance Records\n4. View Grade Transcript\n5. View Fee Details\n6. Secure Logout\nChoice: ";
            cin >> choice;


            if (choice == 1) displayPortal();

            else if (choice == 2){ 
                registerCourse();
            }

            else if (choice == 3) {
                viewAttendance();
            }

            else if (choice == 4) {
                viewTranscript();
            }

            else if (choice == 5) {
                viewFees();
            }

            else if (choice == 6) { 
                cout << "Logging out...\n"; return; 
            }

            else {
                cout << "Invalid Option!\n";
            }

        }

    }
};



// 3. TEACHER CLASS (The Dashboard)

class Teacher : public User {
private:
    string dept;
    string design;


public:

    void setTeacherData(string n, string i, string dep, string des) {
        name = n; id = i; dept = dep; design = des;
    }

    void displayPortal() {
        cout << "\n****************************************************";
        cout << "\n* FACULTY MANAGEMENT SYSTEM           *";
        cout << "\n****************************************************";

        cout << "\n Welcome, Prof. " << name;
        cout << "\n Department: " << dept << " | Role: " << design;
        cout << "\n----------------------------------------------------\n";
    }

    void markAttendance() {
    string searchCode, regID, regCode, date;
    char status;

    cout << "\nEnter Current Date (DD-MM-YYYY): "; cin >> date;
    cout << "Enter Course Code: "; cin >> searchCode;


    ifstream regFile("registrations.txt");
    ofstream attFile("attendance.txt", ios::app);


    cout << "\n--- MARKING ATTENDANCE FOR " << searchCode << " ---\n";

    // FIX: Added string trimming logic
    while (getline(regFile, regID, ',')) {
        if (!getline(regFile, regCode)) break; 

        
        // Remove trailing carriage returns/newlines if they exist
        if (!regCode.empty() && regCode.back() == '\r') regCode.pop_back();

        if (regCode == searchCode) {
            cout << "Student ID: " << regID << " (P/A): ";
            cin >> status;

            attFile << regID << "," << searchCode << "," << (char)toupper(status) << "," << date << endl;
        }

    }

    regFile.close();
    attFile.close();
    cout << "Attendance logs synchronized!\n";

}

    void uploadMarks() {
        string searchCode, regID, regCode;
        float mid, fin;

        cout << "\nEnter Course Code: "; cin >> searchCode;

        ifstream regFile("registrations.txt");
        ofstream marksFile("marks.txt", ios::app);

        cout << "\n--- UPLOADING MARKS FOR " << searchCode << " ---\n";

        while (getline(regFile, regID, ',') && getline(regFile, regCode)) {

            if (regCode == searchCode) {
                cout << "Student ID: " << regID << endl;
                cout << "  Midterm Score (0-30): "; cin >> mid;
                cout << "  Final Exam Score (0-50): "; cin >> fin;

                marksFile << regID << "," << searchCode << "," << mid << "," << fin << endl;
            }

        }

        regFile.close();
        marksFile.close();

        cout << "Marks database updated!\n";
    }


    void teacherDashboard() {
        int choice;

        while(true) {

            cout << "\n--- FACULTY TOOLS ---\n";
            cout << "1. Display Dashboard\n2. Mark Attendance\n3. Upload Exam Marks\n4. Logout\nChoice: ";
            cin >> choice;

            if (choice == 1) displayPortal();

            else if (choice == 2) markAttendance();

            else if (choice == 3) uploadMarks();

            else if (choice == 4) return;

            else cout << "Invalid Choice!\n";

        }

    }
};




// 4. ADMIN CLASS (Central Management)

class Admin : public User {
public:

    void addStudent() {
        string n, id, pass, degree, batch, section;
        string fID, fLine;

        cout << "New Student ID: "; 
        cin >> id;

        ifstream checkFile("students.txt");
        while (getline(checkFile, fID, ',')) {
            if (fID == id) {
                cout << "\n[!] ERROR: Student with ID " << id << " already exists!\n";
                checkFile.close();
                return;
            }
            getline(checkFile, fLine);
        }
        checkFile.close();

        cout << "New Password: "; 
        cin >> pass;
        cin.ignore();

        cout << "Full Name: "; 
        getline(cin, n);

        cout << "Degree: "; 
        cin >> degree;

        cout << "Batch: "; 
        cin >> batch;

        cout << "Section: "; 
        cin >> section;


        ofstream outFile("students.txt", ios::app);
        outFile << id << "," << pass << "," << n << "," << degree << "," << batch << "," << section << endl;
        outFile.close();

        cout << "[SUCCESS] Student account created.\n";
    }


    void addTeacher() {
        string n, tid, pass, dept, des;
        string fID, fLine;

        cout << "New Teacher ID: "; 
        cin >> tid;

        ifstream checkFile("teachers.txt");
        while (getline(checkFile, fID, ',')) {
            if (fID == tid) {
                cout << "\n[!] ERROR: Teacher with ID " << tid << " already exists!\n";
                checkFile.close();
                return;
            }
            getline(checkFile, fLine);
        }
        checkFile.close();

        cout << "New Password: "; 
        cin >> pass;
        cin.ignore();

        cout << "Full Name: "; 
        getline(cin, n);

        cout << "Department: "; 
        cin >> dept;

        cout << "Designation: "; 
        cin >> des;


        ofstream outFile("teachers.txt", ios::app);
        outFile << tid << "," << pass << "," << n << "," << dept << "," << des << endl;
        outFile.close();

        cout << "[SUCCESS] Teacher account created.\n";
    }


    void addCourse() {
        string code, cname, credit;

        cout << "Course Code: "; 
        cin >> code;
        cin.ignore();

        cout << "Course Title: "; 
        getline(cin, cname);

        cout << "Credit Hours: "; 
        cin >> credit;

        ofstream outFile("courses.txt", ios::app);
        outFile << code << "," << cname << "," << credit << endl;
        outFile.close();

        cout << "[SUCCESS] Course added to catalog.\n";
    }


    void viewAllStudents() {
        string fID, fPass, fName, f1, f2, f3;
        ifstream inFile("students.txt");

        cout << "\n--- LIST OF REGISTERED STUDENTS ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "NAME" << "DEGREE" << endl;

        while(getline(inFile, fID, ',') && getline(inFile, fPass, ',') && getline(inFile, fName, ',') &&
              getline(inFile, f1, ',') && getline(inFile, f2, ',') && getline(inFile, f3)) {

            cout << left << setw(10) << fID << setw(20) << fName << f1 << endl;
        }

        inFile.close();
    }
};





// 5. LOGIN SYSTEM

int login(Student &s, Teacher &t) {
    string inID, inPass, fID, fPass, fName, f1, f2, f3;

    cout << "\n--------------------------";
    cout << "\n ENTER SYSTEM CREDENTIALS";
    cout << "\n--------------------------";
    cout << "\n Username/ID: "; cin >> inID;
    cout << " Password: "; cin >> inPass;

    if (inID == "admin" && inPass == "admin123") return 3;


    ifstream sFile("students.txt");

    while (getline(sFile, fID, ',') && getline(sFile, fPass, ',') && getline(sFile, fName, ',') &&
           getline(sFile, f1, ',') && getline(sFile, f2, ',') && getline(sFile, f3)) {

        if (fID == inID && fPass == inPass) {
            s.setStudentData(fName, fID, f1, f2, f3);
            sFile.close(); return 1;

        }

    }

    sFile.close();

    ifstream tFile("teachers.txt");

    while (getline(tFile, fID, ',') && getline(tFile, fPass, ',') && getline(tFile, fName, ',') &&
           getline(tFile, f1, ',') && getline(tFile, f2)) {

        if (fID == inID && fPass == inPass) {
            t.setTeacherData(fName, fID, f1, f2);
            tFile.close(); return 2;

        }

    }

    tFile.close();
    return 0;

}




// 6. MAIN SYSTEM

int main() {
    Admin admin;
    Student curStudent;
    Teacher curTeacher;
    int choice;

    while (true) {

        cout << "\n####################################";
        cout << "\n#      FLEX MANAGEMENT SYSTEM      #";
        cout << "\n####################################";

        cout << "\n1. System Login\n2. Exit Program\nChoice: ";
        cin >> choice;

        if (choice == 1) {

            int type = login(curStudent, curTeacher);

            if (type == 1) { 

                curStudent.displayPortal(); 
                curStudent.studentMenu(); 
            }

            else if (type == 2) { 

                curTeacher.displayPortal(); 
                curTeacher.teacherDashboard(); 
            }

            else if (type == 3) {
                int ac;

                while (true) {

                    cout << "\n--- ADMINISTRATIVE DASHBOARD ---\n1. Register Student\n2. Register Teacher\n3. Add Course\n4. View Student List\n5. Logout\nChoice: ";
                    cin >> ac;

                    if (ac == 1) {
                        admin.addStudent();
                    }

                    else if (ac == 2) {
                        admin.addTeacher();
                    }

                    else if (ac == 3) {
                        admin.addCourse();
                    }

                    else if (ac == 4) {
                        admin.viewAllStudents();
                    }

                    else break;
                }

            }

            else cout << "\n[!] Authentication Failed!\n";

        } 

        else if (choice == 2) {
            cout << "\nTerminating System... Goodbye!\n";
            break;
        }

        else cout << "Invalid Entry!\n";

    }

    return 0;
}

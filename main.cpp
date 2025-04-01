
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <iomanip>

#include "Person.h"
#include "Secretary.h"

using namespace std;

void menu(Secretary & secretary) {
    cout << "****************************************************************\n";
    cout << "                            Main menu\n";
    cout << "****************************************************************\n";

    cout << "  " << setw(4) << "ap: " << setw(20) << "insert professor";
    cout << "  " << setw(4) << "ep: " << setw(20) << "update professor";
    cout << "  " << setw(4) << "dp: " << setw(20) << "delete professor";
    cout << "  " << setw(4) << "pp: " << setw(20) << "print  professors";
    cout << endl;

    cout << "  " << setw(4) << "as: " << setw(20) << "insert student";
    cout << "  " << setw(4) << "es: " << setw(20) << "update student";
    cout << "  " << setw(4) << "ds: " << setw(20) << "delete student";
    cout << "  " << setw(4) << "ps: " << setw(20) << "print  students";
    cout << endl;

    cout << "  " << setw(4) << "ac: " << setw(20) << "insert course";
    cout << "  " << setw(4) << "ec: " << setw(20) << "update course";
    cout << "  " << setw(4) << "dc: " << setw(20) << "delete course";
    cout << "  " << setw(4) << "pc: " << setw(20) << "print  course";
    cout << endl;

    cout << "  " << setw(4) << "aa: " << setw(20) << "insert assignment";
    cout << "  " << setw(4) << "da: " << setw(20) << "delete assignment";
    cout << "  " << setw(4) << "pa: " << setw(20) << "print  assignments";
    cout << endl;

    //8    
    cout << "  " << setw(4) << "ys: " << setw(20) << "student details";
    cout << "  " << setw(4) << "ts: " << setw(20) << "student details for period (year/semester)";
    cout << endl;

    //6    
    cout << "  " << setw(4) << "ss: " << setw(20) << "all students, specific course and period";
    cout << endl;

    //7    
    cout << "  " << setw(4) << "sp: " << setw(20) << "all students, courses of a specific professor for a period";
    cout << endl;




    ///
    /// not implemented
    ///

    //να εγγραφεί ένας φοιτητής σε ένα μάθημα
    cout << "  " << setw(4) << "signup: " << setw(20) << "sign up a student to a course";
    cout << endl;





    //9  να τυπωθούν οι φοιτητές που μπορούν να πάρουν πτυχίο.
    cout << "  " << setw(4) << "gs " << setw(20) << "graduate students";
    cout << endl;


}

string askCommand(Secretary & secretary) {
    while (true) {
        string cmd;

        cout << "Enter your command: ";

        getline(cin, cmd);

        if (cmd == "") {
            menu(secretary);
            continue;
        } else if (cmd == "exit" || cmd == "e" || cmd == "q") {
            return "exit";
        } else if (cmd == "menu" || cmd == "m") {
            menu(secretary);
            continue;
            // ---------------------------------------- professors
        } else if (cmd == "pp") {
            secretary.printProfessors("Professors", cout);
        } else if (cmd == "ap") {
            secretary.addProfessor(cin);
        } else if (cmd == "ep") {
            secretary.editProfessor(cin);
        } else if (cmd == "dp") {
            secretary.deleteProfessor(cin);
            // ---------------------------------------- students
        } else if (cmd == "ps") {
            secretary.printStudents("Students", cout);
        } else if (cmd == "as") {
            secretary.addStudent(cin);
        } else if (cmd == "es") {
            secretary.editStudent(cin);
        } else if (cmd == "ds") {
            secretary.deleteStudent(cin);
            // ---------------------------------------- courses                            
            // TODO:
        } else if (cmd == "pc") {
            secretary.printCourses("Courses", cout);
        } else if (cmd == "ac") {
            secretary.addCourse(cin);
        } else if (cmd == "ec") {
            secretary.editCourse(cin);
        } else if (cmd == "dc") {
            secretary.deleteCourse(cin);
            // ---------------------------------------- assignment   
        } else if (cmd == "pa") {
            secretary.printAssignments("Assignments", cout);
        } else if (cmd == "aa") {
            secretary.addAssignment(cin);
        } else if (cmd == "da") {
            secretary.deleteAssignment(cin);
            // ---------------------------------------- signups   
        } else if (cmd == "pi") {
            secretary.printSignups("Signups", cout);
        } else if (cmd == "ai") {
            //            secretary.addSignup(cin);
        } else if (cmd == "di") {
            //            secretary.deleteAssignment(cin);
            // ---------------------------------------- student details   
        } else if (cmd == "ys") {
            secretary.printStudentDetailsForYear("Your yearly performance ", cin, cout);
        } else if (cmd == "ts") {
            secretary.printStudentDetailsForPeriod("Your semester performance", cin, cout);
            // ---------------------------------------- professor details   
        } else if (cmd == "ss") {
            secretary.printStudentsDetailsForPeriodAndCourse("Course - Period", cin, cout);
        } else if (cmd == "sp") {
            secretary.printStudentsDetailsForPeriodAndProfessor("Professor - Report", cin, cout);

            // ---------------------------------------- error   
        } else {
            cout << "Invalid command" << endl;
        }
    }
}

int main(int argc, char** argv) {
    string professor_filename = "professors.csv";
    string student_filename = "students.csv";
    string course_filename = "courses.csv";
    string assignments_filename = "assignments.csv";
    string signup_filename = "signups.csv";

    Secretary secretary;

    ifstream fp_professors(professor_filename);

    fp_professors >> secretary;

    fp_professors.close();


    ifstream fp_students(student_filename);

    fp_students >> secretary;

    fp_students.close();


    ifstream fp_courses(course_filename);

    fp_courses >> secretary;

    fp_courses.close();


    ifstream fp_assignments(assignments_filename);

    fp_assignments >> secretary;

    fp_assignments.close();

    ifstream fp_signups(signup_filename);

    fp_signups >> secretary;

    fp_signups.close();

    secretary.printProfessors("Professors", cout);
    secretary.printStudents("Students", cout);
    secretary.printCourses("Courses", cout);
    secretary.printAssignments("Assignments", cout);
    secretary.printSignups("Signups", cout);

    while (true) {
        menu(secretary);
        if (askCommand(secretary) == "exit") {
            break;
        }
    }

    return 0;
}


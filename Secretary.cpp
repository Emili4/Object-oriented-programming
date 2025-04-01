
#include <iostream>
#include <sstream>

#include "Secretary.h"
#include "Professor.h"
#include "Student.h"

Secretary::Secretary() {
}

Secretary::Secretary(const Secretary& other) {
    members = other.members;
}

Secretary::~Secretary() {
    for (auto p : members) {
        delete p;
    }
}

void Secretary::operator=(const Secretary& sec) {
    members = sec.members;
}

void Secretary::operator+=(Person * person) {
    members.push_back(person);
}

unsigned int Secretary::get_size() const {
    return members.size();
}

bool Secretary::findPerson(Person * the_person) const {
    for (Person * p : members) {
        if (p == the_person) {
            return true;
        }
    }
    return false;
}

bool Secretary::findPerson(unsigned int the_id) const {
    for (Person * p : members) {
        if (p->get_id_num() == the_id) {
            return true;
        }
    }
    return false;
}

Person * Secretary::getPerson(unsigned int the_id) {
    for (Person * p : members) {
        if (p->get_id_num() == the_id) {
            return p;
        }
    }
    return nullptr;
}

Course * Secretary::getCourse(unsigned int the_id_num) {
    for (Course * p : courses) {
        if (p->get_id_num() == the_id_num) {
            return p;
        }
    }
    return nullptr;
}

ostream & operator<<(ostream & os, const Secretary & s) {
    for (Person * p : s.members) {
        os << *p;
    }

    return os;
}

string Secretary::readString(istream & is) {
    string buffer;
    getline(is, buffer);
    return buffer;
}

unsigned int Secretary::readInt(istream & is) {
    string buffer;
    getline(is, buffer);
    return atoi(buffer.c_str());
}

istream & operator>>(istream & is, Secretary & s) {
    string line;

    while (getline(is, line)) {
        stringstream ss(line);
        string id;

        std::getline(ss, id, ',');

        if (id == "ID") { // ignore 1st line (header)
            continue;
        }

        unsigned int x = atol(id.c_str());

        if (x < 1000 && x > 0) { // professor
            // ID,Name,Surname,Phone,Email,PhD
            std::cout << "Importing professor: " << line << std::endl;

            string token;

            Professor * p = new Professor(x);

            std::getline(ss, token, ',');
            p->set_name(token);

            std::getline(ss, token, ',');
            p->set_surname(token);

            std::getline(ss, token, ',');
            p->set_phone_num(atoi(token.c_str()));

            std::getline(ss, token, ',');
            p->set_email(token);

            std::getline(ss, token, ',');
            p->set_phd_title(token);

            s.members.push_back(p);
        } else if (x > 1900000000) { // student
            // ID,Name,Surname,Phone,Email 
            std::cout << "Importing student: " << line << std::endl;

            string token;

            Student * p = new Student(x);

            std::getline(ss, token, ',');
            p->set_name(token);

            std::getline(ss, token, ',');
            p->set_surname(token);

            std::getline(ss, token, ',');
            p->set_phone_num(atoi(token.c_str()));

            std::getline(ss, token, ',');
            p->set_email(token);

            s.members.push_back(p);
        } else if (x >= 3000 && x <= 4000) { // course
            // ID,Title,Semester,Ects,Mandatory
            std::cout << "Importing student: " << line << std::endl;

            string token;

            Course * p = new Course(x);

            std::getline(ss, token, ',');
            p->set_title(token);

            std::getline(ss, token, ',');
            p->set_semester(atoi(token.c_str()));

            std::getline(ss, token, ',');
            p->set_ects(atoi(token.c_str()));

            std::getline(ss, token, ',');
            p->set_mandatory(token == "yes" || token == "Yes");

            s.courses.push_back(p);
        } else if (x >= 1990 && x <= 2500) { // assignment
            int ctr = 0;

            for (unsigned int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    ctr++;
                }
            }

            if (ctr == 3) {
                std::cout << "Importing assignment: " << line << std::endl;

                string token;

                Period period;

                period.year = x;

                std::getline(ss, token, ',');

                period.semester = atoi(token.c_str());


                PeriodData & periodData = s.data[period];

                std::getline(ss, token, ',');

                unsigned int course_id = atoi(token.c_str());

                std::getline(ss, token, ',');

                unsigned int professor_id = atoi(token.c_str());

                periodData.assignments[course_id] = professor_id;
            } else {
                std::cout << "Importing signup: " << line << std::endl;

                string token;

                Period period;

                period.year = x;

                std::getline(ss, token, ',');

                period.semester = atoi(token.c_str());


                PeriodData & periodData = s.data[period];

                std::getline(ss, token, ',');

                unsigned int course_id = atoi(token.c_str());

                std::getline(ss, token, ',');

                unsigned int student_id = atoi(token.c_str());

                std::getline(ss, token, ',');

                int grade = atoi(token.c_str());

                SignUp signup;

                signup.course_id = course_id;
                signup.grade = (grade >= 0) ? grade : 0;
                signup.graded = (grade >= 0);
                signup.student_id = student_id;

                periodData.signups[course_id].push_back(signup);
            }
        }
    }

    cout << s.data.size() << endl;

    return is;
}

void Secretary::printProfessors(string title, ostream & os) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;

    for (auto instance : members) {
        if (instance->get_id_num() < 1000) {
            cout << *dynamic_cast<Professor*> (instance);
        }
    }
}

void Secretary::printStudents(string title, ostream & os) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;

    for (auto instance : members) {
        if (instance->get_id_num() > 1000) {
            os << *instance;
        }
    }

}

void Secretary::printCourses(string title, ostream & os) {
    cout << "*********************************" << endl;
    cout << "          " << title << endl;
    cout << "*********************************" << endl;

    for (auto instance : courses) {
        os << *instance;
    }
}

//
// Professor
//

void Secretary::addProfessor(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_name;
    string the_surname;
    unsigned int the_phone_num;
    string the_email;
    string the_php_title;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the name: ";
    }

    the_name = readString(is);

    if (prompt) {
        cout << "Type the surname: ";
    }

    the_surname = readString(is);

    if (prompt) {
        cout << "Type the phone number: ";
    }

    the_phone_num = readInt(is);

    if (prompt) {
        cout << "Type the email: ";
    }

    the_email = readString(is);

    if (prompt) {
        cout << "Type phd title: ";
    }

    the_php_title = readString(is);

    Professor * p = new Professor(the_id_num);

    p->set_name(the_name);

    p->set_surname(the_surname);

    p->set_phone_num(the_phone_num);

    p->set_email(the_email);

    p->set_phd_title(the_php_title);

    members.push_back(p);
}

void Secretary::editProfessor(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_name;
    string the_surname;
    unsigned int the_phone_num;
    string the_email;
    string the_php_title;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the name: ";
    }

    the_name = readString(is);

    if (prompt) {
        cout << "Type the surname: ";
    }

    the_surname = readString(is);

    if (prompt) {
        cout << "Type the phone number: ";
    }

    the_phone_num = readInt(is);

    if (prompt) {
        cout << "Type the email: ";
    }

    the_email = readString(is);

    if (prompt) {
        cout << "Type phd title: ";
    }

    the_php_title = readString(is);

    for (list<Person*>::iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            Professor * p = (Professor*) * it;

            p->set_name(the_name);

            p->set_surname(the_surname);

            p->set_phone_num(the_phone_num);

            p->set_email(the_email);

            p->set_phd_title(the_php_title);

            cout << "Professor updated successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

void Secretary::deleteProfessor(istream & is, bool prompt) {
    unsigned int the_id_num;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    for (list<Person*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            members.erase(it);
            cout << "Professor deleted successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

//
// Student
//

void Secretary::addStudent(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_name;
    string the_surname;
    unsigned int the_phone_num;
    string the_email;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the name: ";
    }

    the_name = readString(is);

    if (prompt) {
        cout << "Type the surname: ";
    }

    the_surname = readString(is);

    if (prompt) {
        cout << "Type the phone number: ";
    }

    the_phone_num = readInt(is);

    if (prompt) {
        cout << "Type the email: ";
    }

    the_email = readString(is);

    Student * p = new Student(the_id_num);

    p->set_name(the_name);

    p->set_surname(the_surname);

    p->set_phone_num(the_phone_num);

    p->set_email(the_email);

    members.push_back(p);
}

void Secretary::editStudent(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_name;
    string the_surname;
    unsigned int the_phone_num;
    string the_email;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the name: ";
    }

    the_name = readString(is);

    if (prompt) {
        cout << "Type the surname: ";
    }

    the_surname = readString(is);

    if (prompt) {
        cout << "Type the phone number: ";
    }

    the_phone_num = readInt(is);

    if (prompt) {
        cout << "Type the email: ";
    }

    the_email = readString(is);

    for (list<Person*>::iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            Student * p = (Student*) * it;

            p->set_name(the_name);

            p->set_surname(the_surname);

            p->set_phone_num(the_phone_num);

            p->set_email(the_email);

            cout << "Student updated successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

void Secretary::deleteStudent(istream & is, bool prompt) {
    unsigned int the_id_num;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    for (list<Person*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            members.erase(it);
            cout << "Student deleted successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

void Secretary::addCourse(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_title;
    unsigned int the_semester;
    unsigned int the_ects;
    string the_mandatory;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the title: ";
    }

    the_title = readString(is);

    if (prompt) {
        cout << "Type the the_semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the ects: ";
    }

    the_ects = readInt(is);

    if (prompt) {
        cout << "Type yes or no if the course is mandatory: ";
    }

    the_mandatory = readString(is);

    Course * p = new Course(the_id_num);

    p->set_title(the_title);

    p->set_semester(the_semester);

    p->set_ects(the_ects);

    p->set_mandatory(the_mandatory == "yes");

    courses.push_back(p);
}

void Secretary::editCourse(istream & is, bool prompt) {
    unsigned int the_id_num;
    string the_title;
    unsigned int the_semester;
    unsigned int the_ects;
    string the_mandatory;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    if (prompt) {
        cout << "Type the title: ";
    }

    the_title = readString(is);

    if (prompt) {
        cout << "Type the the_semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the ects: ";
    }

    the_ects = readInt(is);

    if (prompt) {
        cout << "Type yes or no if the course is mandatory: ";
    }

    the_mandatory = readString(is);

    for (list<Course*>::iterator it = courses.begin(); it != courses.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            Course * p = (Course*) * it;

            p->set_title(the_title);

            p->set_semester(the_semester);

            p->set_ects(the_ects);

            p->set_mandatory(the_mandatory == "yes");

            cout << "Course updated successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

void Secretary::deleteCourse(istream & is, bool prompt) {
    unsigned int the_id_num;

    if (prompt) {
        cout << "Type the ID: ";
    }

    the_id_num = readInt(is);

    for (list<Course*>::const_iterator it = courses.begin(); it != courses.end(); ++it) {
        if ((*it)->get_id_num() == the_id_num) {
            courses.erase(it);
            cout << "Course deleted successfully" << endl;
            return;
        }
    }

    cout << "Error: not found \n";
}

void Secretary::printAssignments(string title, ostream & os) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;
    for (auto& entry : data) {
        const Period & period = entry.first;
        const PeriodData & periodData = entry.second;

        cout << "Period: " << period.year << " Semester: " << period.semester << endl;

        for (auto & assignment : periodData.assignments) {
            unsigned int course_id = assignment.first;
            unsigned int professor_id = assignment.second;

            Course * course = getCourse(course_id);
            Person * professor = getPerson(professor_id);

            cout << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << " is assigned to " << professor->get_name() << " " << professor->get_surname() << "(" << professor->get_id_num() << ")" << endl;
        }
    }

}

void Secretary::addAssignment(istream & is, bool prompt) {
    unsigned int the_year;
    unsigned int the_semester;
    unsigned int the_course_id;
    unsigned int the_professor_id;

    if (prompt) {
        cout << "Type the year: ";
    }

    the_year = readInt(is);

    if (prompt) {
        cout << "Type the semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the course_id: ";
    }

    the_course_id = readInt(is);

    if (prompt) {
        cout << "Type the professor id: ";
    }

    the_professor_id = readInt(is);

    Period period;

    period.year = the_year;

    period.semester = the_semester;

    PeriodData & periodData = data[period];

    periodData.assignments[the_course_id] = the_professor_id;
}

void Secretary::deleteAssignment(istream & is, bool prompt) {
    unsigned int the_year;
    unsigned int the_semester;
    unsigned int the_course_id;

    if (prompt) {
        cout << "Type the year: ";
    }

    the_year = readInt(is);

    if (prompt) {
        cout << "Type the semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the course_id: ";
    }

    the_course_id = readInt(is);

    Period period;

    period.year = the_year;

    period.semester = the_semester;

    PeriodData & periodData = data[period];

    periodData.assignments.erase(the_course_id);
}

void Secretary::printSignups(string title, ostream & os) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;
    for (auto& entry : data) {
        const Period & period = entry.first;
        const PeriodData & periodData = entry.second;

        cout << "Period: " << period.year << " Semester: " << period.semester << endl;

        for (auto & signup : periodData.signups) {
            unsigned int course_id = signup.first;
            const vector<SignUp> & signups = signup.second;

            Course * course = getCourse(course_id);

            cout << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << ":" << endl;
            for (const SignUp & signup : signups) {
                Person * student = getPerson(signup.student_id);

                cout << "       Student: " << student->get_name() << " " << student->get_surname() << "(" << student->get_id_num() << ")";

                if (signup.graded) {
                    cout << " - grade: " << signup.grade << endl;
                } else {
                    cout << " - grade: pending" << endl;
                }

            }
        }
    }
}

void Secretary::printSignups(string title, ostream & os, unsigned int student_id) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;
    for (auto& entry : data) {
        const Period & period = entry.first;
        const PeriodData & periodData = entry.second;

        bool valid_for_specific_student = false;

        for (auto & signup : periodData.signups) {
            const vector<SignUp> & signups = signup.second;

            for (const SignUp & signup : signups) {
                if (signup.student_id == student_id) {
                    valid_for_specific_student = true;
                    break;
                }
            }
        }

        if (valid_for_specific_student) {
            cout << "Period: " << period.year << " Semester: " << period.semester << endl;

            for (auto & signup : periodData.signups) {
                unsigned int course_id = signup.first;
                const vector<SignUp> & signups = signup.second;

                Course * course = getCourse(course_id);

                cout << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << ":" << endl;
                for (const SignUp & signup : signups) {
                    if (signup.student_id == student_id) {
                        Person * student = getPerson(signup.student_id);
                        cout << "       Student: " << student->get_name() << " " << student->get_surname() << "(" << student->get_id_num() << ")";

                        if (signup.graded) {
                            cout << " - grade: " << signup.grade << endl;
                        } else {
                            cout << " - grade: pending" << endl;
                        }
                    }
                }
            }
        }
    }
}

void Secretary::printSignups(string title, ostream & os, unsigned int student_id, Period desiredPeriod) {
    os << "*********************************" << endl;
    os << "          " << title << endl;
    os << "*********************************" << endl;
    for (auto& entry : data) {
        const Period & period = entry.first;
        const PeriodData & periodData = entry.second;

        if (period.semester != desiredPeriod.semester || period.year != desiredPeriod.year) {
            continue;
        }

        bool valid_for_specific_student = false;

        for (auto & signup : periodData.signups) {
            const vector<SignUp> & signups = signup.second;

            for (const SignUp & signup : signups) {
                if (signup.student_id == student_id) {
                    valid_for_specific_student = true;
                    break;
                }
            }
        }

        if (valid_for_specific_student) {
            cout << "Period: " << period.year << " Semester: " << period.semester << endl;

            for (auto & signup : periodData.signups) {
                unsigned int course_id = signup.first;
                const vector<SignUp> & signups = signup.second;

                Course * course = getCourse(course_id);

                cout << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << ":" << endl;
                for (const SignUp & signup : signups) {
                    if (signup.student_id == student_id) {
                        Person * student = getPerson(signup.student_id);
                        cout << "       Student: " << student->get_name() << " " << student->get_surname() << "(" << student->get_id_num() << ")";

                        if (signup.graded) {
                            cout << " - grade: " << signup.grade << endl;
                        } else {
                            cout << " - grade: pending" << endl;
                        }
                    }
                }
            }
        }
    }
}

void Secretary::printCourseSignups(string title, ostream & os, unsigned int desiredCourseId, Period desiredPeriod) {
    os << "******************************************************************" << endl;
    os << "          " << title << endl;
    os << "******************************************************************" << endl;
    for (auto& entry : data) {
        const Period & period = entry.first;
        const PeriodData & periodData = entry.second;

        if (period.semester != desiredPeriod.semester || period.year != desiredPeriod.year) {
            continue;
        }

        bool valid_for_specific_course = false;

        for (auto & signup : periodData.signups) {
            const vector<SignUp> & signups = signup.second;

            for (const SignUp & signup : signups) {
                if (signup.course_id == desiredCourseId) {
                    valid_for_specific_course = true;
                    break;
                }
            }
        }

        ofstream fp_out("output_6.txt");

        if (valid_for_specific_course) {
            cout << "Period: " << period.year << " Semester: " << period.semester << endl;

            for (auto & signup : periodData.signups) {
                unsigned int course_id = signup.first;
                const vector<SignUp> & signups = signup.second;

                Course * course = getCourse(course_id);

                if (course_id == desiredCourseId) {
                    cout << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << ":" << endl;
                    fp_out << "   " << "Course " << course->get_title() << "(" << course->get_id_num() << ")" << ":" << endl;
                    for (const SignUp & signup : signups) {
                        Person * student = getPerson(signup.student_id);
                        cout << "       Student: " << student->get_name() << " " << student->get_surname() << "(" << student->get_id_num() << ")";
                        fp_out << "       Student: " << student->get_name() << " " << student->get_surname() << "(" << student->get_id_num() << ")";

                        if (signup.graded) {
                            cout << " - grade: " << signup.grade << endl;
                            fp_out << " - grade: " << signup.grade << endl;
                        } else {
                            fp_out << " - grade: pending" << endl;
                        }
                    }
                }
            }
        }
    }


}

void Secretary::Secretary::addSignup(istream & is, bool prompt) {

}

void Secretary::Secretary::deleteSignup(istream & is, bool prompt) {

}

void Secretary::printStudentDetailsForYear(string title, istream & is, ostream & os, bool prompt) {
    unsigned int the_student_id;

    if (prompt) {
        cout << "Type the the_student_id: ";
    }

    the_student_id = readInt(is);

    printSignups(title, os, the_student_id);
}

void Secretary::printStudentDetailsForPeriod(string title, istream & is, ostream & os, bool prompt) {
    unsigned int the_year;
    unsigned int the_semester;
    unsigned int the_student_id;

    if (prompt) {
        cout << "Type the year: ";
    }

    the_year = readInt(is);

    if (prompt) {
        cout << "Type the semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the the_student_id: ";
    }

    the_student_id = readInt(is);

    Period period;

    period.year = the_year;
    period.semester = the_semester;

    printSignups(title, os, the_student_id, period);
}

void Secretary::printStudentsDetailsForPeriodAndCourse(string title, istream & is, ostream & os, bool prompt) {
    unsigned int the_year;
    unsigned int the_semester;
    unsigned int the_course_id;

    if (prompt) {
        cout << "Type the year: ";
    }

    the_year = readInt(is);

    if (prompt) {
        cout << "Type the semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the the_course_id: ";
    }

    the_course_id = readInt(is);


    Period period;

    period.year = the_year;
    period.semester = the_semester;

    printCourseSignups(title, os, the_course_id, period);

}

void Secretary::printStudentsDetailsForPeriodAndProfessor(string title, istream & is, ostream & os, bool prompt) {
    unsigned int the_year;
    unsigned int the_semester;
    unsigned int the_professor_id;

    if (prompt) {
        cout << "Type the year: ";
    }

    the_year = readInt(is);

    if (prompt) {
        cout << "Type the semester: ";
    }

    the_semester = readInt(is);

    if (prompt) {
        cout << "Type the professor ID: ";
    }

    the_professor_id = readInt(is);


    Period period;

    period.year = the_year;
    period.semester = the_semester;


    PeriodData & periodData = data[period];


    os << "******************************************************************" << endl;
    os << "                     " << title << endl;
    os << "******************************************************************" << endl;
    cout << "Period: " << period.year << " Semester: " << period.semester << endl;

    for (auto & assignment : periodData.assignments) {
        unsigned int course_id = assignment.first;
        unsigned int professor_id = assignment.second;

        if (professor_id == the_professor_id) {
            printCourseSignups(title + " - course: " + getCourse(course_id)->get_title(), os, course_id, period);
            cout << endl;
        }
    }

    cout << endl;
}


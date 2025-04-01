
#ifndef SECRETARY_H
#define SECRETARY_H

#include <list>

#include "Person.h"
#include "Course.h"
#include "PeriodData.h"
#include "Period.h"

using namespace std;

class Secretary {
private:
    list<Person*> members; // students and professors
    list<Course*> courses;
    map<Period, PeriodData> data;
    
    string readString(istream & is);
    unsigned int readInt(istream & is);
    
public:
    Secretary();
    Secretary(const Secretary&);
    ~Secretary();

    void operator+=(Person *);

    void operator=(const Secretary&);

    unsigned int get_size() const;

    friend ostream & operator<<(ostream &, const Secretary &);
    friend istream & operator>>(istream &, Secretary &);

    bool findPerson(Person *) const;
    bool findPerson(unsigned int) const;
    
    Person * getPerson(unsigned int);
    Course * getCourse(unsigned int );
    
    
    void printProfessors(string title, ostream & os);
    void addProfessor(istream & is, bool prompt = true);
    void editProfessor(istream & is, bool prompt = true);
    void deleteProfessor(istream & is, bool prompt = true);
    
    void printStudents(string title, ostream & os);
    void addStudent(istream & is, bool prompt = true);
    void editStudent(istream & is, bool prompt = true);
    void deleteStudent(istream & is, bool prompt = true);
    
    void printCourses(string title, ostream & os);
    void addCourse(istream & is, bool prompt = true);
    void editCourse(istream & is, bool prompt = true);
    void deleteCourse(istream & is, bool prompt = true);
    
    
    
    
    void printAssignments(string title, ostream & os);
    void addAssignment(istream & is, bool prompt = true);
    void deleteAssignment(istream & is, bool prompt = true);
    
    void printSignups(string title, ostream & os);
    void printSignups(string title, ostream & os, unsigned int student_id);
    void printSignups(string title, ostream & os, unsigned int student_id, Period period);
    void printCourseSignups(string title, ostream & os, unsigned int course_id, Period period);
    void addSignup(istream & is, bool prompt = true);
    void deleteSignup(istream & is, bool prompt = true);
    
    
    void printStudentDetailsForYear(string title, istream & is, ostream & os, bool prompt = true);
    void printStudentDetailsForPeriod(string title, istream & is, ostream & os, bool prompt = true);
    
    void printStudentsDetailsForPeriodAndCourse(string title, istream & is, ostream & os, bool prompt = true);
    void printStudentsDetailsForPeriodAndProfessor(string title, istream & is, ostream & os, bool prompt = true);
};

ostream & operator<<(ostream &, const Secretary & );

istream & operator>>(istream &, Secretary & );

#endif /* SECRETARY_H */


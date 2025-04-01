
#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

class Course {
private:
    unsigned int id_num;
    string title;
    unsigned int semester; // 1-8
    unsigned int ects;
    bool mandatory;
    static int counter;
public:
    Course(unsigned int the_id_num);
    Course(unsigned int the_id_num, string the_title, unsigned int the_semester, unsigned int the_ects, bool the_mandatory);
    virtual ~Course();

    void set_ects(unsigned int ects);
    void set_mandatory(bool mandatory);
    void set_semester(unsigned int semester);
    void set_title(string title);

    unsigned int get_id_num() const;
    unsigned int get_ects() const;
    bool get_mandatory() const;
    unsigned int get_semester() const;
    string get_title() const;

    static int get_counter();
    
    friend ostream & operator<<(ostream & os, const Course &);
    friend istream & operator>>(istream & is, Course &);
};


#endif /* COURSE_H */



#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

#include <string>

using namespace std;

class Student : public Person {
public:
    Student(unsigned int the_id_num);
    Student(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email);
    virtual ~Student();
private:

};

#endif /* STUDENT_H */


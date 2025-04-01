#include "Student.h"


Student::Student(unsigned int the_id_num) : Person(the_id_num) {
    
}

Student::Student(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email) :
Person(the_name, the_surname, the_id_num, the_phone_num, the_email) {
}

Student::~Student() {
}


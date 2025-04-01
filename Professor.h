
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Person.h"

class Professor : public Person {
public:
    Professor(unsigned int the_id_num);
    Professor(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email, string the_phd_title);
    virtual ~Professor();
    
    string get_phd_title() const;

    void set_phd_title(string phd_title);
private:
    string phd_title;

    friend ostream & operator<<(ostream &, const Professor &);
};

ostream & operator<<(ostream &, const Professor &);

#endif /* PROFESSOR_H */


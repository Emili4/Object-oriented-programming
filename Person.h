#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

// - encapsulation
// - c-tor
// - d-tor
// - overload >>
// - overload <<
// - total objects

//----------------------- Class Person -----------------------//

class Person {
protected:
    string name;
    string surname;
    const unsigned int id_num;
    unsigned int phone_num;
    string email;
    static int counter;
public:
    Person(unsigned int the_id_num);
    Person(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email);
    virtual ~Person();

    void set_name(string);
    void set_surname(string);
    void set_phone_num(unsigned int);
    void set_email(string);


    string get_name() const;
    string get_surname() const;
    unsigned int get_id_num() const;
    unsigned int get_phone_num() const;
    string get_email() const;

    static int get_counter();
    
    friend ostream & operator<<(ostream & os, const Person &);
    friend istream & operator>>(istream & is, Person &);
};

ostream & operator<<(ostream &, const Person &);

istream & operator>>(istream &, Person &);

#endif /* PERSON_H */


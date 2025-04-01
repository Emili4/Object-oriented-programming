#include <iostream>
#include <iomanip>
#include <string>
#include "Person.h"


using namespace std;

int Person::counter = 0;

int Person::get_counter() {
    return counter;
}


//---------------------- Class Person -----------------------//

Person::Person(unsigned int the_id_num) : id_num(the_id_num) {
    name = "";
    surname = "";
    phone_num = 0;
    email = "";
    counter++;

    cout << "Person " << the_id_num << " has been created! (anonymous) " << endl;
}

Person::Person(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email) : id_num(the_id_num) {
    name = the_name;
    surname = the_surname;
    phone_num = the_phone_num;
    email = the_email;
    counter++;

    cout << "Person " << the_id_num << " " << name << " has been created! " << endl;
}

Person::~Person() {
    cout << "Person " << id_num << " " << name << "is about to be destroyed!" << endl;
}

void Person::set_name(string the_name) {
    name = the_name;
}

void Person::set_surname(string the_surname) {
    surname = the_surname;
}

void Person::set_phone_num(unsigned int the_phone_num) {
    phone_num = the_phone_num;
}

void Person::set_email(string the_email) {
    email = the_email;
}

string Person::get_name() const {
    return name;
}

string Person::get_surname() const {
    return surname;
}

unsigned int Person::get_id_num() const {
    return id_num;
}

unsigned int Person::get_phone_num() const {
    return phone_num;
}

string Person::get_email() const {
    return email;
}

ostream & operator<<(ostream & os, const Person & p) {
    os << setw(3) << left << p.get_id_num() << "\t";
    os << setw(15) << left << p.get_name() << "\t";
    os << setw(15) << left << p.get_surname() << "\t";
    os << setw(30) << left << p.get_email() << "\t";
    os << setw(10) << left << p.get_phone_num() << "\t";

    os << endl;

    return os;
}

istream & operator>>(istream & is, Person & p) {
    is >> p.name;
    is >> p.surname;
    is >> p.email;
    is >> p.phone_num;

    return is;
}
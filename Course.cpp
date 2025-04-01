#include <iomanip>
#include "Course.h"

#include <iostream>

using namespace std;

int Course::counter = 0;

unsigned int Course::get_ects() const {
    return ects;
}

bool Course::get_mandatory() const {
    return mandatory;
}

unsigned int Course::get_semester() const {
    return semester;
}

string Course::get_title() const {
    return title;
}

void Course::set_ects(unsigned int ects) {
    this->ects = ects;
}

void Course::set_mandatory(bool mandatory) {
    this->mandatory = mandatory;
}

void Course::set_semester(unsigned int semester) {
    this->semester = semester;
}

void Course::set_title(string title) {
    this->title = title;
}

int Course::get_counter() {
    return counter;
}

Course::Course(unsigned int the_id_num, string the_title, unsigned int the_semester, unsigned int the_ects, bool the_mandatory) {
    id_num = the_id_num;
    title = the_title;
    semester = the_semester;
    ects = the_ects;
    mandatory = the_mandatory;
    counter++;

    cout << "Course " << id_num << " " << title << " " << semester << " " << ects << " " << mandatory << " " << counter << endl;
}

Course::Course(unsigned int the_id_num) : id_num(the_id_num) {
}

Course::~Course() {
}

unsigned int Course::get_id_num() const {
    return id_num;
}

ostream & operator<<(ostream & os, const Course & p) {
    os << setw(3) << left << p.get_id_num() << "\t";
    os << setw(15) << left << p.get_title() << "\t";
    os << setw(15) << left << p.get_semester() << "\t";
    os << setw(30) << left << p.get_ects() << "\t";
    os << setw(10) << left << p.get_mandatory() << "\t";

    os << endl;

    return os;
}

// istream & operator>>(istream & is, Course &) {

// }
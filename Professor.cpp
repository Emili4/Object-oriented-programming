#include <iomanip>
#include "Professor.h"

using namespace std;

Professor::Professor(unsigned int the_id_num) : Person(the_id_num) {

}

Professor::Professor(string the_name, string the_surname, unsigned int the_id_num, unsigned int the_phone_num, string the_email, string the_phd_title) :
Person(the_name, the_surname, the_id_num, the_phone_num, the_email) {
    phd_title = the_phd_title;
}

Professor::~Professor() {
}

string Professor::get_phd_title() const {
    return phd_title;
}

void Professor::set_phd_title(string the_phd_title) {
    phd_title = the_phd_title;
}

ostream & operator<<(ostream & os, const Professor & p) {
    os << setw(3) << left << p.get_id_num() << "\t";
    os << setw(15) << left << p.get_name() << "\t";
    os << setw(15) << left << p.get_surname() << "\t";
    os << setw(30) << left << p.get_email() << "\t";
    os << setw(10) << left << p.get_phone_num() << "\t";
    os << setw(10) << left << p.get_phd_title() << "\t";

    os << endl;

    return os;
}

#ifndef PERIODDATA_H
#define PERIODDATA_H

#include <map>
#include <vector>

#include "SignUp.h"

using namespace std;

struct PeriodData {
    map<unsigned int, unsigned int> assignments; // course id => professor id
    
    map<unsigned int, vector<SignUp>> signups; // course id => student ids
};

#endif /* PERIODDATA_H */


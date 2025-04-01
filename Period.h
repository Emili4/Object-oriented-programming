#ifndef PERIOD_H
#define PERIOD_H

struct Period {
public:
    int year;
    int semester; // 1-8
    
    bool operator<(const Period & other) const {
        int key = year*100000+semester;
        int other_key = other.year*100000+other.semester;
        
        return key < other_key;
    }
};

#endif /* PERIOD_H */


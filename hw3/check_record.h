#ifndef CHECK_RECORD_H
#define CHECK_RECORD_H

#include "mytime.h"

enum CheckType {
    IN, OUT,
};

class CheckRecord {
    private:
        int id;
        CheckType type;
        MyTime timestamp;
    public:
        CheckRecord(int id, CheckType type, MyTime timestamp);
        
        bool operator < (const CheckRecord &o2) const;

        int getID() const;
        CheckType getType() const;
        MyTime getTimestamp() const;
};
#endif

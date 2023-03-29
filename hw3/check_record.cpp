#include "check_record.h"
#include "mytime.h"

CheckRecord::CheckRecord(int id, CheckType type, MyTime timestamp) {
    this->id = id;
    this->type = type;
    this->timestamp = timestamp;
}

bool CheckRecord::operator < (const CheckRecord &o2) const {
    return timestamp < o2.timestamp;
}

int CheckRecord::getID() const {
    return id;
}

CheckType CheckRecord::getType() const {
    return type;
}
    
MyTime CheckRecord::getTimestamp() const {
    return timestamp;
}
#include "sign_record.h"
#include "date.h"

SignRecord::SignRecord(int id, SignType type, Date timestamp) {
    this->id = id;
    this->type = type;
    this->timestamp = timestamp;
}

bool SignRecord::operator < (const SignRecord &o2) const {
    if (type != o2.type) {
        return type == IN;
    }
    return timestamp < o2.timestamp;
}

int SignRecord::getID() const {
    return id;
}

SignType SignRecord::getType() const {
    return type;
}
    
Date SignRecord::getTimestamp() const {
    return timestamp;
}
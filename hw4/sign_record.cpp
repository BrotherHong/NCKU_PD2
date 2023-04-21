#include "sign_record.h"
#include "date.h"

SignRecord::SignRecord(int id, SignType type, Date date) :
    id(id), type(type), date(date) {}

bool SignRecord::operator < (const SignRecord &o2) const {
    if (type != o2.type) {
        return type == IN;
    }
    return date < o2.date;
}

int SignRecord::getID() const {
    return id;
}

SignType SignRecord::getType() const {
    return type;
}
    
Date SignRecord::getDate() const {
    return date;
}
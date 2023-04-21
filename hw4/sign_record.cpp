#include "sign_record.h"
#include "date.h"

SignRecord::SignRecord(int id, SignType type, Date date) :
    id(id), type(type), date(date) {}

bool SignRecord::operator < (const SignRecord &o2) const {
    if (id != o2.id) {
        return id < o2.id;
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
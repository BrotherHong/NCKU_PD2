#ifndef SIGN_RECORD_H
#define SIGN_RECORD_H

#include "date.h"

enum SignType {
    IN, OUT,
};

class SignRecord {
    private:
        int id;
        SignType type;
        Date timestamp;
    public:
        SignRecord(int id, SignType type, Date timestamp);
        
        bool operator < (const SignRecord &o2) const;

        int getID() const;
        SignType getType() const;
        Date getTimestamp() const;
};
#endif

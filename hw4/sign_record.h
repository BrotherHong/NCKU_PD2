#ifndef SIGN_RECORD_H
#define SIGN_RECORD_H

#include "date.h"

enum SignType {
    IN, OUT,
};

class SignRecord {
    public:
        SignRecord(int id, SignType type, Date timestamp);
        
        bool operator < (const SignRecord &o2) const;

        int getID() const;
        SignType getType() const;
        Date getTimestamp() const;

    private:
        int id;
        SignType type;
        Date timestamp;
};
#endif

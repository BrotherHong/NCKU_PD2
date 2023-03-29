#ifndef MYTIME_H
#define MYTIME_H

#include<string>
using namespace std;

class MyTime {
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;

        long long getTotalMinutes() const;

    public:
        MyTime();
        MyTime(int year, int month, int day, int hour, int minute);

        bool operator < (const MyTime &o2) const;
        long long operator - (const MyTime &o2) const;

        int getYear() const;
        int getMonth() const;
        int getDate() const;
        int getHour() const;
        int getMinute() const;
};

MyTime fromYYYYMMDDhhmm(string str);

bool isSameDate(const MyTime &o1, const MyTime &o2);

#endif

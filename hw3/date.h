#ifndef DATE_H
#define DATE_H

#include<string>
using namespace std;

class Date {
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;

        long long getTotalMinutes() const;

    public:
        Date();
        Date(int year, int month, int day, int hour, int minute);

        bool operator < (const Date &o2) const;
        long long operator - (const Date &o2) const;

        int getYear() const;
        int getMonth() const;
        int getDate() const;
        int getHour() const;
        int getMinute() const;
};

Date fromString(string str);

bool isSameDay(const Date &o1, const Date &o2);

#endif

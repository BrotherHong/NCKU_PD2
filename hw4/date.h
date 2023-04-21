#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Date {
    public:
        static Date fromString(string str);

        Date();
        Date(int year, int month, int day, int hour, int minute);

        friend ostream& operator<<(ostream &os, const Date &date);
        bool operator < (const Date &o2) const;

        int getYear() const;
        int getMonth() const;
        int getDate() const;
        int getHour() const;
        int getMinute() const;

    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
};

#endif

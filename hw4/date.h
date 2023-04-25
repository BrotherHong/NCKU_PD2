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
        friend bool isSameDate(const Date &d1, const Date &d2);
        friend bool isConsecutiveDate(const Date &d1, const Date &d2);
        friend int getTotalDay(const Date &d);
        bool operator < (const Date &o2) const;

        inline int getYear() const;
        inline int getMonth() const;
        inline int getDate() const;
        inline int getHour() const;
        inline int getMinute() const;

    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
};

#endif

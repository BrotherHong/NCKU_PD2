#include "date.h"

#include <string>
using namespace std;

Date::Date() : Date(0, 0, 0, 0, 0) {}

Date::Date(int year, int month, int day, int hour, int minute) :
    year(year), month(month), day(day), hour(hour), minute(minute) {}

bool Date::operator < (const Date &o2) const {
    if (year != o2.year) {
        return year < o2.year;
    }
    if (month != o2.month) {
        return month < o2.month;
    }
    if (day != o2.day) {
        return day < o2.day;
    }
    if (hour != o2.hour) {
        return hour < o2.hour;
    }
    if (minute != o2.minute) {
        return minute < o2.minute;
    }
    return false;
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDate() const {
    return day;
}

int Date::getHour() const {
    return hour;
}

int Date::getMinute() const {
    return minute;
}

Date Date::fromString(string str) {
    int Y, M, D, h, m;

    sscanf(str.c_str(), "%04d%02d%02d%02d%02d", &Y, &M, &D, &h, &m);

    return Date(Y, M, D, h, m);
}

ostream& operator<<(ostream &os, const Date &date) {
    os << setfill('0') 
        << setw(4) << date.year 
        << setw(2) << date.month 
        << setw(2) << date.day;
    return os;
}

bool isSameDate(const Date &d1, const Date &d2) {
    if (d1.year != d2.year) {
        return false;
    }
    if (d1.month != d2.month) {
        return false;
    }
    if (d1.day != d2.day) {
        return false;
    }
    return true;
}

bool isLeapYear(int year);

bool isConsecutiveDate(const Date &d1, const Date &d2) {
    int day1 = getTotalDay(d1);
    int day2 = getTotalDay(d2);
    return (day2 - day1 == 1);
}

// From 2012
int getTotalDay(const Date &d) {
    int days = 0;
    const int daysOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int daysOfYear = 365;

    for (int y = 2012; y < d.year; y++) {
        days += daysOfYear + isLeapYear(y);
    }

    for (int m = 1; m < d.month; m++) {
        days += daysOfMonth[m];
        if (m == 2) {
            days += isLeapYear(d.year);
        }
    }
    days += d.day;

    return days;
}

bool isLeapYear(int year) {
    return (year%400 == 0 || (year%4 == 0 && year%100 != 0));
}


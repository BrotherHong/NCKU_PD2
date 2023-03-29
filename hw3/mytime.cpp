#include "mytime.h"
#include <string>

using namespace std;

MyTime::MyTime() : MyTime(0, 0, 0, 0, 0) {}

MyTime::MyTime(int year, int month, int day, int hour, int minute) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}

bool MyTime::operator < (const MyTime &o2) const {
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

long long MyTime::operator - (const MyTime &o2) const {
    return getTotalMinutes() - o2.getTotalMinutes();
}

int MyTime::getYear() const {
    return year;
}

int MyTime::getMonth() const {
    return month;
}

int MyTime::getDate() const {
    return day;
}

int MyTime::getHour() const {
    return hour;
}

int MyTime::getMinute() const {
    return minute;
}

long long MyTime::getTotalMinutes() const {
    long long t = year;

    t *= 12; // 12 month per year
    t += month;
    t *= 30; // approx 30 day per month
    t += day;
    t *= 24; // 24 hr per day
    t += hour;
    t *= 60; // 60 min per hr
    t += minute;
    
    return t;
}

MyTime fromYYYYMMDDhhmm(string str) {
    int Y, M, D, h, m;

    sscanf(str.c_str(), "%04d%02d%02d%02d%02d", &Y, &M, &D, &h, &m);

    return MyTime(Y, M, D, h, m);
}

bool isSameDate(const MyTime &o1, const MyTime &o2) {
    if (o1.getYear() != o2.getYear()) return false;
    if (o1.getMonth() != o2.getMonth()) return false;
    return o1.getDate() == o2.getDate();
}


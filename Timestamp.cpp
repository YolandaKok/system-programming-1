//
// Created by yolanda on 8/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Timestamp.h"

Timestamp::Timestamp(int day, int month, int year, int hour, int minutes) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minutes = minutes;
}

int Timestamp::isBetweenHour(int hour1, int minutes1, int hour2, int minutes2) {
    struct tm t = {};
    time_t t_of_day, t_of_day2, t_of_day3;

    t.tm_hour = this->hour;
    t.tm_min = this->minutes;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);


    t.tm_hour = hour1;
    t.tm_min = minutes1;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day2 = mktime(&t);


    t.tm_hour = hour2;
    t.tm_min = minutes2;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day3 = mktime(&t);

    if((t_of_day - t_of_day2 >= 0) && ((t_of_day3 - t_of_day) >=0)) {
        return 1;
    }
    return 0;
}

int Timestamp::isBetweenDays(int hour1, int minutes1, int day1, int month1, int year1, int hour2, int minutes2, int day2, int month2, int year2) {
    struct tm t = {};
    time_t t_of_day, t_of_day2, t_of_day3;

    t.tm_year = this->year - 1900;
    t.tm_mon = this->month;           // Month, 0 - jan
    t.tm_mday = this->day;
    t.tm_hour = this->hour;
    t.tm_min = this->minutes;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);

    t.tm_year = year1 - 1900;
    t.tm_mon = month1;           // Month, 0 - jan
    t.tm_mday = day1;
    t.tm_hour = hour1;
    t.tm_min = minutes1;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day2 = mktime(&t);

    t.tm_year = year2 - 1900;
    t.tm_mon = month2;           // Month, 0 - jan
    t.tm_mday = day2;
    t.tm_hour = hour2;
    t.tm_min = minutes2;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day3 = mktime(&t);


    if((t_of_day - t_of_day2 >= 0) && ((t_of_day3 - t_of_day) >=0)) {
        return 1;
    }
    return 0;
}

/* Print the timestamp */
void Timestamp::print() {
    if(this->minutes < 10) {
        printf(" %d-%d-%d %d:0%d\n", this->day, this->month, this->year, this->hour, this->minutes);
    } else {
        printf(" %d-%d-%d %d:%d\n", this->day, this->month, this->year, this->hour, this->minutes);
    }
}

Timestamp::~Timestamp() {

}
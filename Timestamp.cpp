//
// Created by yolanda on 8/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "Timestamp.h"

Timestamp::Timestamp(int day, int month, int year, int hour, int minutes) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minutes = minutes;
}

/* Find if it is less than */
int Timestamp::isLessThan(Timestamp& t2) {
    if(this->day <= t2.day && this->month <= t2.month && this->year <= t2.year && this->hour <= t2.hour && this->minutes <= t2.minutes)
        return 1;
    return 0;
}

int Timestamp::isBetweenHour(int hour1, int minutes1, int hour2, int minutes2) {
    if(((hour1 <= this->hour) && (this->hour <= hour2)) && ((minutes1 <= this->minutes) && (this->minutes <= minutes2)) )
        return 1;
    return 0;
}

Timestamp::~Timestamp() {

}
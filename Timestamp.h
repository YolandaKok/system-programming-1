//
// Created by yolanda on 8/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_TIMESTAMP_H
#define SYSTEM_PROGRAMMING_1_TIMESTAMP_H

#include <stdio.h>
#include <stdlib.h>

class Timestamp {
    private:
        int day;
        int month;
        int year;
        int hour;
        int minutes;
    public:
        Timestamp(int, int ,int , int, int);
        /* Functions that gives me if the d1 is less than d2 including hour */
        int isBetween(Timestamp&, Timestamp&);
        int isBetweenDays(int, int, int, int, int, int, int, int, int, int);
        int isBetweenHour(int, int, int, int);
        void print();
        ~Timestamp();

};

#endif //SYSTEM_PROGRAMMING_1_TIMESTAMP_H

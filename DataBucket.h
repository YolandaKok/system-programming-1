//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_DATABUCKET_H
#define SYSTEM_PROGRAMMING_1_DATABUCKET_H
#include "Transaction.h"

class DataBucket {
    private:
        char name[50];
        /* Pointer to a transaction linked list */
        Transaction *head;
    public:
        DataBucket();
        DataBucket(char name[50]);
        void setName(char name[50]);
        char* getName();
        void printName();
        ~DataBucket();
};

#endif //SYSTEM_PROGRAMMING_1_DATABUCKET_H

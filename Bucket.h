//
// Created by yolanda on 26/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BUCKET_H
#define SYSTEM_PROGRAMMING_1_BUCKET_H

#include "Transaction.h"

class Bucket {
    private:
        void *records;
        Bucket *next;
        int remainingBytes;
        int offset;
    public:
        Bucket(int bytes);
        int sizeInBytes();
        int addUser(char *name, Transaction *transaction);
        int addTransaction(char* user, Transaction *transaction);
        int findUser(char *name);
        void printTransactions(char *userId);
        //int addTransaction(char *name, Transaction *transaction);
        void traverseTransactions(char *user, Transaction *transaction);
        Bucket* getNext();
        void printUsers();
        ~Bucket();

};

#endif //SYSTEM_PROGRAMMING_1_BUCKET_H

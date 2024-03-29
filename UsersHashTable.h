//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_UsersHashTable_H
#define SYSTEM_PROGRAMMING_1_UsersHashTable_H

#include "Transaction.h"
#include "Bucket.h"
#include "WalletHashTable.h"
#include "TreeHashTable.h"

class WalletHashTable;
class TreeHashTable;

class Bucket;
class Transaction;

class UsersHashTable {
    private:
        int size;
        int bucketSize;
        Bucket **buckets;
    public:
        UsersHashTable(int size, int bytes);
        int hashFunction(char *userId);
        /* Add Transaction to the bucket */
        int addTransaction(char *user, Transaction *transaction);
        void printUsers();
        void printUsersBucket(int i);
        void traverseTransactions(char *user, Transaction *transaction, WalletHashTable *walletHashTable,
                TreeHashTable *treeHashTable);
        void printTransactions(char* userId);
        void printTransactions(char* userId, int hour1, int minutes1, int hour2, int minutes2);
        void printTransactions(char* userId, int hour1, int minutes1, int day1, int month1, int year1,
                                           int hour2, int minutes2, int day2, int month2, int year2);
        int getEarnings (char *userId);
        int getEarnings (char *userId, int hour1, int minutes1, int hour2, int minutes2);
        int getEarnings (char *userId, int hour1, int minutes1, int day1, int month1, int year1, int hour2,
                                     int minutes2, int day2, int month2, int year2);
        ~UsersHashTable();
};

#endif //SYSTEM_PROGRAMMING_1_UsersHashTable_H

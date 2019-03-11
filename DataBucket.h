//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_DATABUCKET_H
#define SYSTEM_PROGRAMMING_1_DATABUCKET_H
#include "Transaction.h"
#include "UsersHashTable.h"

#include "WalletHashTable.h"
#include "TreeHashTable.h"

class TreeHashTable;

class WalletHashTable;

class DataBucket {
    private:
        char name[50];
        /* Pointer to a transaction linked list */
        Transaction *head;
    public:
        DataBucket();
        DataBucket(char name[50]);
        void setName(char name[50]);
        void setTransactionListHead(Transaction *transaction);
        void removeTransactions();
        Transaction* getTransactionListHead();
        void addTransaction(Transaction *head, Transaction *transaction);
        char* getName();
        void printTransactions();
        void printTransactions(int day1, int minutes1, int day2, int minutes2);
        void printTransactions(int hour1, int minutes1, int day1, int month1, int year1, int hour2, int minutes2,
                                       int day2, int month2, int year2);
        void traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
                WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);
        void printName();
        int getEarnings();
        int getEarnings(int hour1, int minutes1, int hour2, int minutes2);
        int getEarnings(int hour1, int minutes1, int day1, int month1, int year1, int hour2, int minutes2, int day2, int month2, int year2);
        ~DataBucket();
};

#endif //SYSTEM_PROGRAMMING_1_DATABUCKET_H

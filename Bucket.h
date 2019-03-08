//
// Created by yolanda on 26/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BUCKET_H
#define SYSTEM_PROGRAMMING_1_BUCKET_H

#include "Transaction.h"
#include "UsersHashTable.h"
#include "WalletHashTable.h"

#include "TreeHashTable.h"


class TreeHashTable;

class WalletHashTable;
class UsersHashTable;
class Transaction;

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
        void traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
                WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);
        Bucket* getNext();
        void printUsers();
        int getEarnings(char *userId);
        int getEarnings(char *userId, int hour1, int minutes1, int hour2, int minutes2);
        ~Bucket();

};

#endif //SYSTEM_PROGRAMMING_1_BUCKET_H

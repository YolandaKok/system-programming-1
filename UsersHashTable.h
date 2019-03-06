//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_UsersHashTable_H
#define SYSTEM_PROGRAMMING_1_UsersHashTable_H

#include "Transaction.h"
#include "Bucket.h"
#include "WalletHashTable.h"

class WalletHashTable;

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
        void insertSender(char *sender);
        /* Add Transaction to the bucket */
        int addTransaction(char *user, Transaction *transaction);
        void printUsers();
        void traverseTransactions(char *user, Transaction *transaction, WalletHashTable *walletHashTable);
        void printTransactions(char* userId);
        ~UsersHashTable();
};

#endif //SYSTEM_PROGRAMMING_1_UsersHashTable_H

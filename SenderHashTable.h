//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H
#define SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H

#include "Transaction.h"
#include "Bucket.h"

class SenderHashTable {
    private:
        int size;
        int bucketSize;
        Bucket **buckets;
    public:
        SenderHashTable(int size, int bytes);
        int hashFunction(char *userId);
        void insertSender(char *sender);
        /* Add Transaction to the bucket */
        int addTransaction(Transaction *transaction);
        void printTransactions(char* userId);
        ~SenderHashTable();
};

#endif //SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H

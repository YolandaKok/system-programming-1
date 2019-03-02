//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_IOUTILS_H
#define SYSTEM_PROGRAMMING_1_IOUTILS_H

#include "SenderHashTable.h"

/* Read the arguments from the command line */
int readArgs(int argc, char* argv[], char*& bitCoinBalancesFile, char*& transactionsFile, int& bitcoinValue,
        int& senderHashtableNumOfEntries, int& receiverHashtableNumOfEntries, int& bucketSize);

/* Read Coins Balance File */
int readCoinsBalance( FILE *fp, char* bitCoinBalancesFile, int coinValue);

/* Read Transactions */
int readTransactions( FILE *fp, char* transactionsFile, SenderHashTable *senderHashTable);

#endif //SYSTEM_PROGRAMMING_1_IOUTILS_H

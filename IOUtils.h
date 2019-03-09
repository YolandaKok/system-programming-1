//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_IOUTILS_H
#define SYSTEM_PROGRAMMING_1_IOUTILS_H

#include "UsersHashTable.h"
#include "WalletHashTable.h"
#include "TreeHashTable.h"

/* Read the arguments from the command line */
int readArgs(int argc, char* argv[], char*& bitCoinBalancesFile, char*& transactionsFile, int& bitcoinValue,
        int& UsersHashTableNumOfEntries, int& receiverHashtableNumOfEntries, int& bucketSize);

/* Read Coins Balance File */
int readCoinsBalance( FILE *fp, char* bitCoinBalancesFile, int coinValue, UsersHashTable *receiverHashTable,
        UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);

/* Read Transactions */
int readTransactions( FILE *fp, char* transactionsFile, UsersHashTable *receiverHashTable,
                      UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);

int dateIsValid(int day, int month, int year, int hour, int minutes);

#endif //SYSTEM_PROGRAMMING_1_IOUTILS_H

//
// Created by yolanda on 9/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_USERCOMMANDS_H
#define SYSTEM_PROGRAMMING_1_USERCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "UserCommands.h"
#include "UsersHashTable.h"
#include "TreeHashTable.h"
#include "WalletHashTable.h"

int requestTransaction(char *token, UsersHashTable *receiverHashTable,
                       UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);
void requestTransactions(char *line, UsersHashTable *receiverHashTable, UsersHashTable *senderHashTable,
                         WalletHashTable *walletHashTable, TreeHashTable *treeHashTable);
int findBitCoinStatus(char *, TreeHashTable*, int);
void findEarnings(char *userId, UsersHashTable *usersHashTable, char *token, int payments);

#endif //SYSTEM_PROGRAMMING_1_USERCOMMANDS_H

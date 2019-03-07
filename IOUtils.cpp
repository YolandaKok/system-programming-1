//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "IOUtils.h"
#include "Wallet.h"
#include "Transaction.h"
#include "UsersHashTable.h"
#include "TreeHashTable.h"
#include "WalletHashTable.h"
#include "CoinNode.h"

/* Read the arguments */
int readArgs(int argc, char* argv[], char*& bitCoinBalancesFile, char*& transactionsFile, int& bitcoinValue,
             int& UsersHashTableNumOfEntries, int& receiverHashtableNumOfEntries, int& bucketSize) {
    int i;
    for ( i = 1; i < argc; i+=2 ) {
        if(!strcmp(argv[i], "-a")) {
            bitCoinBalancesFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(bitCoinBalancesFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-t")) {
            transactionsFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(transactionsFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-v")) {
            bitcoinValue = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-h1")) {
            UsersHashTableNumOfEntries = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-h2")) {
            receiverHashtableNumOfEntries = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-b")) {
            bucketSize = atoi(argv[i+1]);
        }
    }
}

/* Read Coins Balance File */
int readCoinsBalance( FILE *fp, char* bitCoinBalancesFile, int coinValue, UsersHashTable *receiverHashTable,
                      UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    ListNode *list = NULL;
    //Wallet *wallet;
    char *userId;
    Transaction *transaction;
    CoinNode *coinNode;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        /* get the first token */
        token = strtok(line, " ");
        int count = 0;
        list = NULL;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                userId = (char*)malloc(strlen(token) + 1);
                strcpy(userId, token);
                printf("Userid %s \n", userId);
            }
            else {
                if(count == 1) {
                    //printf("Coin Id: %s", token);
                    coinNode = treeHashTable->insert(token, userId, coinValue);
                    transaction = new Transaction();
                    transaction->setReceiver(userId);
                    transaction->setSender(userId);
                    transaction->setAmount(coinValue);
                    transaction->setTransactionId("1");
                    transaction->setVirtualTransaction(1);
                    /* Add the CoinNode List Head */
                    transaction->setCoinNodeListHead(coinNode);
                    receiverHashTable->addTransaction(userId, transaction);
                    list = new ListNode(token, coinValue);
                }
                else {
                    coinNode = treeHashTable->insert(token, userId, coinValue);
                    transaction = new Transaction();
                    transaction->setReceiver(userId);
                    transaction->setSender(userId);
                    transaction->setAmount(coinValue);
                    transaction->setTransactionId("2");
                    transaction->setVirtualTransaction(1);
                    /* Set CoinNode List Head for virtual transaction */
                    transaction->setCoinNodeListHead(coinNode);
                    receiverHashTable->addTransaction(userId, transaction);
                    list->insert(token, list);
                }
            }
            token = strtok(NULL, " ");
            count++;
        }
        if( list != NULL ) {
            walletHashTable->insert(userId, list);
        }
        else {
            //printf("%s !@# \n", userId);
        }
        free(userId);
    }
    //walletHashTable->print("Kylian");
    //int balance = walletHashTable->getBalance("Ioanna");
    treeHashTable->print();
    //delete treeHashTable;

    fclose(fp);
    free(line);
}

int readTransactions( FILE *fp, char* transactionsFile, UsersHashTable *receiverHashTable,
                      UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    Transaction *transaction, *transaction1;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        transaction = new Transaction();
        transaction1 = new Transaction();
        /* get the first token */
        token = strtok(line, " ");
        int count = 0;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                // printf("TransactionID: %s \n", token);
                transaction->setTransactionId(token);
                transaction1->setTransactionId(token);
            }
            else if(count == 1) {
                // printf("SenderWalletID: %s \n", token);
                transaction->setSender(token);
                transaction1->setSender(token);
            }
            else if(count == 2) {
                // printf("ReceiverWalletID: %s \n", token);
                transaction->setReceiver(token);
                transaction1->setReceiver(token);
            }
            else if(count == 3) {
                // printf("Value: %s \n", token);
                transaction->setAmount(atoi(token));
                /* It's the transaction that we want to pass */
                transaction1->setRemainder(atoi(token));
                transaction1->setAmount(atoi(token));
            }
            else if(count == 4) {
                // printf("Date: %s \n", token);
            }
            else if(count == 5) {
                // printf("Time: %s \n", token);
            }
            token = strtok(NULL, " ");
            count++;
        }
        transaction->setVirtualTransaction(0);
        transaction1->setVirtualTransaction(0);
        int balance = walletHashTable->getBalance(transaction->getSender());
        /* Let's do the transaction */
        if( balance > transaction->getAmount() ) {
            printf("We can do the transaction !\n");
            printf("%s %d BALANCE\n", transaction->getSender(), balance);
            /* Traverse the receiverHashTable and the virtual nodes */
            receiverHashTable->traverseTransactions(transaction->getSender(), transaction1, walletHashTable);
            //receiverHashTable->addTransaction(transaction->getSender(), transaction);
            /* For every node, testify if it is leaf */
            /* If it is a leaf go to the CoinNode and find the amount on this node */
            /* Create two new nodes, One with the amount left to the initial user, the right node and one with the amount transfered to the other user */
            /* Update the wallets of the two users */
            /* If the amount is not transfered go to the next transaction node and do the same until you transfer all the amount to the receiver */
            /* Return the CoinNodes */
        }
        else {
            printf("Transaction Error !");
        }
        /* Insert into UsersHashTable */
        senderHashTable->addTransaction(transaction->getSender(), transaction);
        //receiverHashTable->addTransaction(transaction1->getReceiver(), transaction1);
    }

    fclose(fp);
    free(line);
}
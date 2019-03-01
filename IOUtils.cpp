//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOUtils.h"
#include "Wallet.h"
#include "HashTable.h"
#include "Transaction.h"
#include "SenderHashTable.h"

/* Read the arguments */
int readArgs(int argc, char* argv[], char*& bitCoinBalancesFile, char*& transactionsFile, double& bitcoinValue,
             int& senderHashtableNumOfEntries, int& receiverHashtableNumOfEntries, int& bucketSize) {
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
            bitcoinValue = atof(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-h1")) {
            senderHashtableNumOfEntries = atoi(argv[i+1]);
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
int readCoinsBalance( FILE *fp, char* bitCoinBalancesFile) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    ListNode *list;
    Wallet *wallet;
    char *userId;
    HashTable *hashTable;
    hashTable = new HashTable(10);

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        /* get the first token */
        token = strtok(line, " ");
        int count = 0;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                //printf("userId: %s \n", token);
                userId = (char*)malloc(strlen(token) + 1);
                strcpy(userId, token);
                printf("User Hash: %d \n", hashTable->hashFunction(token));
            }
            else {
                if(count == 1) {
                    list = new ListNode(token);
                }
                else {
                    list->insert(token, list);
                }
            }
            token = strtok(NULL, " ");
            count++;
        }
        //list->print(list);
        wallet = new Wallet(list);
        hashTable->insertUser(userId, wallet);
        free(userId);
        //delete wallet;
    }

    //hashTable->printUsers();
    hashTable->printUsersWallet("Ioanna");
    delete hashTable;

    fclose(fp);
    free(line);
}

int readTransactions( FILE *fp, char* transactionsFile, SenderHashTable *senderHashTable) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    Transaction *transaction;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        transaction = new Transaction();
        /* get the first token */
        token = strtok(line, " ");
        int count = 0;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                printf("TransactionID: %s \n", token);
                transaction->setTransactionId(token);
            }
            else if(count == 1) {
                printf("SenderWalletID: %s \n", token);
                transaction->setSender(token);
            }
            else if(count == 2) {
                printf("ReceiverWalletID: %s \n", token);
                transaction->setReceiver(token);
            }
            else if(count == 3) {
                printf("Value: %s \n", token);
                transaction->setAmount(atoi(token));
            }
            else if(count == 4) {
                printf("Date: %s \n", token);
            }
            else if(count == 5) {
                printf("Time: %s \n", token);
            }
            token = strtok(NULL, " ");
            count++;
        }
        /* Insert into senderHashTable */
        senderHashTable->addTransaction(transaction);
    }
    delete senderHashTable;

    fclose(fp);
    free(line);
}
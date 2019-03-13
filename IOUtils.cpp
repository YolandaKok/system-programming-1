//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include "IOUtils.h"
#include "Wallet.h"
#include "Transaction.h"
#include "UsersHashTable.h"
#include "TreeHashTable.h"
#include "WalletHashTable.h"
#include "CoinNode.h"

int current_transaction_id = 0;
int current_hour = -1, current_minutes = -1, current_day = -1, current_month = -1, current_year = -1;

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
    int length;

    char *t_id;
    t_id = (char*)malloc(strlen("3") + 1);
    strcpy(t_id, "3");

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        /* get the first token */
        length = strlen(line);
        if( line[length-1] == '\n' )
            line[length-1] = 0;
        token = strtok(line, " ");
        int count = 0;
        list = NULL;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                userId = (char*)malloc(strlen(token) + 1);
                strcpy(userId, token);
                if(walletHashTable->find(userId)) {
                    printf("User with ID: %s already exists !\n", userId);
                    free(userId);
                    free(line);
                    fclose(fp);
                    free(t_id);
                    return 0;
                }
            }
            else {
                if(count == 1) {
                    if(treeHashTable->findCoin(token)) {
                        printf("Bitcoin with ID: %s already exists !\n", token);
                        free(userId);
                        free(line);
                        fclose(fp);
                        free(t_id);
                        return 0;
                    }
                    coinNode = treeHashTable->insert(token, userId, coinValue);
                    transaction = new Transaction();
                    transaction->setReceiver(userId);
                    transaction->setSender(userId);
                    transaction->setAmount(coinValue);
                    transaction->setTransactionId(t_id);
                    transaction->setVirtualTransaction(1);
                    /* Add the CoinNode List Head */
                    transaction->setCoinNodeListHead(coinNode);
                    receiverHashTable->addTransaction(userId, transaction);
                    list = new ListNode(token, coinValue);
                }
                else {
                    if(treeHashTable->findCoin(token)) {
                        printf("Error with transaction file !\n");
                        free(userId);
                        free(line);
                        fclose(fp);
                        free(t_id);
                        return 0;
                    }
                    coinNode = treeHashTable->insert(token, userId, coinValue);
                    transaction = new Transaction();
                    transaction->setReceiver(userId);
                    transaction->setSender(userId);
                    transaction->setAmount(coinValue);
                    transaction->setTransactionId(t_id);
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
        free(userId);
    }

    free(t_id);

    fclose(fp);
    free(line);
    return 1;
}

int readTransactions( FILE *fp, char* transactionsFile, UsersHashTable *receiverHashTable,
                      UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token = NULL, *token1 = NULL;
    int length, posn;
    Transaction *transaction = NULL, *transaction1 = NULL;
    int day, month, year, hour, minutes;
    /* Structure to keep the date and time */


    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        length = strlen(line);
        if( line[length-1] == '\n' )
            line[length-1] = 0;
        transaction = new Transaction();
        transaction1 = new Transaction();
        /* get the first token */
        token = strtok(line, " ");
        int count = 0;
        /* walk through other tokens */
        while( token != NULL ) {
            if(count == 0) {
                if(atoi(token) > current_transaction_id) {
                    current_transaction_id = atoi(token);
                }
                transaction->setTransactionId(token);
                transaction1->setTransactionId(token);
            }
            else if(count == 1) {
                transaction->setSender(token);
                transaction1->setSender(token);
            }
            else if(count == 2) {
                transaction->setReceiver(token);
                transaction1->setReceiver(token);
            }
            else if(count == 3) {
                transaction->setAmount(atoi(token));
                /* It's the transaction that we want to pass */
                transaction1->setRemainder(atoi(token));
                transaction1->setAmount(atoi(token));
            }
            else if(count == 4) {
                char *token2 = token;
                token1 = strtok_r(token2, "-", &token2);
                day = atoi(token1);
                token1 = strtok_r(NULL, "-", &token2);
                month = atoi(token1);
                token1 = strtok_r(NULL, " ", &token2);
                year = atoi(token1);
            }
            else if(count == 5) {
                char *token3 = token;
                token1 = strtok(token3, ":");
                hour = atoi(token1);
                token1 = strtok(NULL, ":");
                minutes = atoi(token1);
            }
            token = strtok(NULL, " ");
            count++;
        }
        Timestamp *timestamp = new Timestamp(day, month, year, hour, minutes);
        Timestamp *timestamp1 = new Timestamp(day, month, year, hour, minutes);
        /* Create a timestamp */
        transaction->setTimestamp(timestamp);
        transaction1->setTimestamp(timestamp1);

        transaction->setVirtualTransaction(0);
        transaction1->setVirtualTransaction(0);
        int balance = walletHashTable->getBalance(transaction->getSender());
        if(strcmp(transaction->getSender(), transaction->getReceiver()) != 0) {
            /* Let's do the transaction */
            if( (balance - transaction->getAmount()) >= 0) {

                if(dateIsValid(day, month, year, hour, minutes) ) {
                    current_day = day; current_minutes = minutes; current_year = year; current_hour = hour; current_month = month;
                    receiverHashTable->traverseTransactions(transaction->getSender(), transaction1, walletHashTable, treeHashTable);
                    senderHashTable->addTransaction(transaction->getSender(), transaction);
                }
                else {
                    printf("Failed ! Error with transaction time !\n");
                    delete transaction; delete transaction1;
                }

                /* For every node, testify if it is leaf */
                /* If it is a leaf go to the CoinNode and find the amount on this node */
                /* Create two new nodes, One with the amount left to the initial user, the right node and one with the amount transfered to the other user */
                /* Update the wallets of the two users */
                /* If the amount is not transfered go to the next transaction node and do the same until you transfer all the amount to the receiver */
                /* Return the CoinNodes */
            }
            else {
                /* User Has not enough money to make the transactiond */
                printf("Transaction failed. User: %s has not enough money in his / her wallet. \n", transaction->getSender());
                delete transaction; delete transaction1;
            }
        }
        else {
            printf("Sender has to be different from receiver !\n");
            delete transaction; delete transaction1;
        }
    }

    fclose(fp);
    free(line);
}

int dateIsValid(int day, int month, int year, int hour, int minutes) {
    struct tm t = { 0 };
    time_t t_of_day, t_of_day2;

    t.tm_year = year - 1900;
    t.tm_mon = month;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minutes;
    t.tm_isdst = -1;
    t_of_day = mktime(&t);

    t.tm_year = current_year - 1900;
    t.tm_mon = current_month;
    t.tm_mday = current_day;
    t.tm_hour = current_hour;
    t.tm_min = current_minutes;
    t.tm_isdst = -1;
    t_of_day2 = mktime(&t);

    if((t_of_day - t_of_day2) >= 0) {
        return 1;
    }
    else {
        return 0;
    }

}
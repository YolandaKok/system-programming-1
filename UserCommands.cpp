//
// Created by yolanda on 9/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "UserCommands.h"
#include "IOUtils.h"

extern int current_transaction_id;
extern int current_day, current_month, current_year, current_hour, current_minutes;

int requestTransaction(char *line, UsersHashTable *receiverHashTable,
                       UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {

    printf("%d CURRENT TRANSACTION ID\n", current_transaction_id);
    int day, month, year, hour, minutes;
    char *token = NULL, *token1 = NULL;
    int length, posn;
    int balance = 0;
    Transaction *transaction, *transaction1;
    printf("Inside request transaction %s \n", line);
    /* Find the senderWallet, receiverWallet, Day, Time */
    transaction = new Transaction();
    transaction1 = new Transaction();
    /* get the first token */
    token = strtok(NULL, " ");
    int count = 0;
    /* walk through other tokens */
    while( token != NULL ) {

        if(count == 0) {
            // printf("SenderWalletID: %s \n", token);
            transaction->setSender(token);
            transaction1->setSender(token);
        }
        else if(count == 1) {
            // printf("ReceiverWalletID: %s \n", token);
            transaction->setReceiver(token);
            transaction1->setReceiver(token);
        }
        else if(count == 2) {
            // printf("Value: %s \n", token);
            transaction->setAmount(atoi(token));
            /* It's the transaction that we want to pass */
            transaction1->setRemainder(atoi(token));
            transaction1->setAmount(atoi(token));
        }
        else if(count == 3) {
            printf("Date: %s \n", token);
            char *token2 = NULL;
            token2 = token;
            token1 = strtok_r(token2, "-", &token2);
            printf("%s Day\n", token1);
            day = atoi(token1);
            token1 = strtok_r(NULL, "-", &token2);
            month = atoi(token1);
            printf("%s Month\n", token1);
            token1 = strtok_r(NULL, " ", &token2);
            year = atoi(token1);
            printf("%s Year\n", token1);
            printf("%s tttt\n", token);
        }
        else if(count == 4) {
            char *token3 = NULL;
            token3 = token;
            printf("HOURRRRR %s\n", token);
            token1 = strtok(token3, ":");
            hour = atoi(token1);
            printf("%s Hour\n", token1);
            token1 = strtok(NULL, ":");
            minutes = atoi(token1);
            printf("%s Minutes\n", token1);
        }
        token = strtok(NULL, " ");
        count++;
        printf("token %s \n", token);
    }
    Timestamp *timestamp = new Timestamp(day, month, year, hour, minutes);
    Timestamp *timestamp1 = new Timestamp(day, month, year, hour, minutes);
    /* Create a timestamp */
    transaction->setTimestamp(timestamp);
    transaction1->setTimestamp(timestamp1);

    current_transaction_id += 1;

    char *id = NULL;
    int totalDigits, no = current_transaction_id + 1;
    while(no!=0){
        //4
        no = no/10;
        totalDigits ++;
    }
    id = (char*)malloc(totalDigits + 1);
    sprintf(id, "%d", current_transaction_id);

    printf("%s YEAAAAH\n", id);

    transaction->setTransactionId(id);
    transaction1->setTransactionId(id);

    free(id);

    transaction->setVirtualTransaction(0);
    transaction1->setVirtualTransaction(0);
    balance = walletHashTable->getBalance(transaction->getSender());
    printf("%d %d %d %d %d \n", current_day, current_month, current_year, current_hour, current_minutes);
    /* Let's do the transaction */
    if( balance > transaction->getAmount() ) {
        if(dateIsValid(day, month, year, hour, minutes)) {
            current_day = day; current_minutes = minutes; current_year = year; current_hour = hour; current_month = month;
            receiverHashTable->traverseTransactions(transaction->getSender(), transaction1, walletHashTable, treeHashTable);
            senderHashTable->addTransaction(transaction->getSender(), transaction);
        }
        else {
            printf("Failed ! Error with transaction time !\n");
            delete transaction; delete transaction1;
        }
    }
    else {
        /* User Has not enough money to make the transactiond */
        printf("Transaction failed. User: %s has not enough money in his / her wallet. \n", transaction->getSender());
        delete transaction; delete transaction1;
    }
    /* Do the transaction */
}

/* Request Transactions from command line */
void requestTransactions(char *line, UsersHashTable *receiverHashTable, UsersHashTable *senderHashTable,
        WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    char *token;
    token = strtok(NULL, ";");
    char *token2 = token;
    char *token1;
    char *token3, *token4;

    while( token != NULL ) {
        printf("%s whatttt\n", token);
        token2 = token;
        token1 = strtok_r(token2, " ", &token2);
        int count = 0;
        while( token1 != NULL ) {
            count++;
            if(count == 4) {
                printf("%s lololo\n", token1);
                token3 = token1;
                token4 = strtok_r(token3, "-", &token3);
                printf("%s day\n", token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s month\n", token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s year\n", token4);
            }
            if(count == 5) {
                printf("%s lololo\n", token1);
                token3 = token1;
                token4 = strtok_r(token3, ":", &token3);
                printf("%s hour\n", token4);
                token4 = strtok_r(NULL, ":", &token3);
                printf("%s minutes\n", token4);
            }
            token1 = strtok_r(token2, " ", &token2);
        }
        token = strtok(NULL, ";");
    }
}
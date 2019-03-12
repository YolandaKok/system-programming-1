//
// Created by yolanda on 9/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include "UserCommands.h"
#include "IOUtils.h"

extern int current_transaction_id;
extern int current_day, current_month, current_year, current_hour, current_minutes;

int requestTransaction(char *line, UsersHashTable *receiverHashTable,
                       UsersHashTable *senderHashTable, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {

    int day, month, year, hour, minutes;
    char *token = NULL, *token1 = NULL;
    int length, posn;
    int balance = 0;
    Transaction *transaction, *transaction1;
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
            char *token2 = NULL;
            token2 = token;
            token1 = strtok_r(token2, "-", &token2);
            day = atoi(token1);
            token1 = strtok_r(NULL, "-", &token2);
            month = atoi(token1);
            token1 = strtok_r(NULL, " ", &token2);
            year = atoi(token1);
        }
        else if(count == 4) {
            char *token3 = NULL;
            token3 = token;
            token1 = strtok(token3, ":");
            hour = atoi(token1);
            token1 = strtok(NULL, ":");
            minutes = atoi(token1);
        }
        token = strtok(NULL, " ");
        count++;
    }

    printf("%d COUNTTTT\n", count);

    if(count == 3) {
        /* Insert the current date and time */
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        day = tm.tm_mday;
        month = tm.tm_mon + 1;
        year = tm.tm_year + 1900;
        hour = tm.tm_hour;
        minutes = tm.tm_min;
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
    /* Let's do the transaction */
    if( (balance - transaction->getAmount()) >= 0) {
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
}

void requestTransactionsFile(FILE *fp, UsersHashTable *receiverHashTable, UsersHashTable *senderHashTable,
        WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token = NULL, *token1 = NULL;
    int length, posn;
    Transaction *transaction = NULL, *transaction1 = NULL;
    int day, month, year, hour, minutes;

    getline(&line, &len, fp);

    int balance;
    token = strtok(line, ";");
    char *token2 = token;
    char *token3, *token4;
    Timestamp *timestamp, *timestamp1;



    while( token != NULL ) {
        transaction = new Transaction();
        transaction1 = new Transaction();
        printf("%s whatttt\n", token);
        token2 = token;
        token1 = strtok_r(token2, " ", &token2);
        int count = 0;
        while( token1 != NULL ) {
            if(count == 0) {
                printf("SenderWalletID: %s \n", token1);
                transaction->setSender(token1);
                transaction1->setSender(token1);
            }
            else if(count == 1) {
                printf("ReceiverWalletID: %s \n", token1);
                transaction->setReceiver(token1);
                transaction1->setReceiver(token1);
            }
            else if(count == 2) {
                printf("Value: %s \n", token1);
                transaction->setAmount(atoi(token1));
                /* It's the transaction that we want to pass */
                transaction1->setRemainder(atoi(token1));
                transaction1->setAmount(atoi(token1));
            }
            if(count == 3) {
                token3 = token1;
                token4 = strtok_r(token3, "-", &token3);
                printf("%s day\n", token4);
                day = atoi(token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s month\n", token4);
                month = atoi(token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s year\n", token4);
                year = atoi(token4);
            }
            if(count == 4) {
                printf("%s lololo\n", token1);
                token3 = token1;
                token4 = strtok_r(token3, ":", &token3);
                printf("%s hour\n", token4);
                hour = atoi(token4);
                token4 = strtok_r(NULL, ":", &token3);
                printf("%s minutes\n", token4);
                minutes = atoi(token4);
            }
            count++;
            token1 = strtok_r(token2, " ", &token2);
        }


        // TODO: Make this a function
        /* Let's do that for one transaction */

        timestamp = new Timestamp(day, month, year, hour, minutes);
        timestamp1 = new Timestamp(day, month, year, hour, minutes);
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
        if( (balance - transaction->getAmount()) >= 0)  {
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
        /* End of the transaction */
        token = strtok(NULL, ";");
    }

    fclose(fp);
    free(line);

}

/* Request Transactions from command line */
void requestTransactions(char *line, UsersHashTable *receiverHashTable, UsersHashTable *senderHashTable,
        WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {

    int day, month, year, hour, minutes;

    char *token;
    int balance;
    token = strtok(NULL, ";");
    char *token2 = token;
    char *token1;
    char *token3, *token4;
    Timestamp *timestamp, *timestamp1;
    Transaction *transaction, *transaction1;


    while( token != NULL ) {
        transaction = new Transaction();
        transaction1 = new Transaction();
        printf("%s whatttt\n", token);
        token2 = token;
        token1 = strtok_r(token2, " ", &token2);
        int count = 0;
        while( token1 != NULL ) {
            if(count == 0) {
                printf("SenderWalletID: %s \n", token1);
                transaction->setSender(token1);
                transaction1->setSender(token1);
            }
            else if(count == 1) {
                printf("ReceiverWalletID: %s \n", token1);
                transaction->setReceiver(token1);
                transaction1->setReceiver(token1);
            }
            else if(count == 2) {
                printf("Value: %s \n", token1);
                transaction->setAmount(atoi(token1));
                /* It's the transaction that we want to pass */
                transaction1->setRemainder(atoi(token1));
                transaction1->setAmount(atoi(token1));
            }
            if(count == 3) {
                token3 = token1;
                token4 = strtok_r(token3, "-", &token3);
                printf("%s day\n", token4);
                day = atoi(token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s month\n", token4);
                month = atoi(token4);
                token4 = strtok_r(NULL, "-", &token3);
                printf("%s year\n", token4);
                year = atoi(token4);
            }
            if(count == 4) {
                printf("%s lololo\n", token1);
                token3 = token1;
                token4 = strtok_r(token3, ":", &token3);
                printf("%s hour\n", token4);
                hour = atoi(token4);
                token4 = strtok_r(NULL, ":", &token3);
                printf("%s minutes\n", token4);
                minutes = atoi(token4);
            }
            count++;
            token1 = strtok_r(token2, " ", &token2);
        }


        // TODO: Make this a function
        /* Let's do that for one transaction */

        timestamp = new Timestamp(day, month, year, hour, minutes);
        timestamp1 = new Timestamp(day, month, year, hour, minutes);
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
        if( (balance - transaction->getAmount()) >= 0)  {
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
        /* End of the transaction */
        token = strtok(NULL, ";");
    }
}


void findEarnings(char *userId, UsersHashTable *receiverHashTable, char *token, int payments) {
    char *token2 = token;
    char *token1;
    int hour1 = -1, minutes1 = -1, hour2 = -1, minutes2 = -1, day1 = -1;
    int month1 = -1, year1 = -1, day2 = -1, month2 = -1, year2 = -1;
    int earnings;
    hour1 = atoi(token);
    token = strtok(NULL, " ");
    minutes1 = atoi(token);
    token2 = strtok(NULL, " ");
    token1 = strtok_r(token2, "-", &token2);
    if(strlen(token2) > 2) {
        day1 = atoi(token1);
        token1 = strtok_r(token2, "-", &token2);
        month1 = atoi(token1);
        token1 = strtok_r(NULL, "-", &token2);
        year1 = atoi(token1);
    }
    if(year1 == -1) {
        token1 = strtok(token1, ":");
        hour2 = atoi(token1);
        token1 = strtok(NULL, ":");
        minutes2 = atoi(token1);
    }
    else {
        token2 = strtok(NULL, " ");
        token1 = strtok_r(token2, ":", &token2);
        hour2 = atoi(token1);
        token1 = strtok_r(NULL, " ", &token2);
        minutes2 = atoi(token1);
    }
    token2 = strtok(NULL, " ");
    token1 = strtok_r(token2, "-", &token2);
    if(token1 != NULL) {
        day2 = atoi(token1);
        token1 = strtok_r(token2, "-", &token2);
        month2 = atoi(token1);
        token1 = strtok_r(NULL, "-", &token2);
        year2 = atoi(token1);
    }
    if( year1 == -1 && year2 == -1 ) {
        earnings = receiverHashTable->getEarnings(userId, hour1, minutes1, hour2, minutes2);
        /* Print the transactions between these hours */
        /* New function for this */
        if( payments ) {
            printf("WalletId: %s Payments: %d \n", userId, earnings);
        }
        else {
            printf("WalletId: %s Earnings: %d \n", userId, earnings);
        }
        receiverHashTable->printTransactions(userId, hour1, minutes1, hour2, minutes2);
    }
    else {
        earnings = receiverHashTable->getEarnings(userId, hour1, minutes1, day1, month1, year1,
                                                  hour2, minutes2, day2, month2, year2);
        if( payments ) {
            printf("WalletId: %s Payments: %d \n", userId, earnings);
        }
        else {
            printf("WalletId: %s Earnings: %d \n", userId, earnings);
        }
        receiverHashTable->printTransactions(userId, hour1, minutes1, day1, month1, year1,
                                             hour2, minutes2, day2, month2, year2);
    }

}


int findBitCoinStatus(char *bitCoinId, TreeHashTable *treeHashTable, int initialValue) {
    int unspent = treeHashTable->findUnspent(bitCoinId);
    /* Find The number of transactions */
    int num_of_transactions = treeHashTable->findNumberOfTransactions(bitCoinId);
    printf("Initial Value: %d Transactions: %d Unspent: %d \n", initialValue, num_of_transactions, unspent);
}
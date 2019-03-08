//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "IOUtils.h"
#include "Bucket.h"
#include "DataBucket.h"
#include "UsersHashTable.h"
#include "TreeHashTable.h"

int main(int argc, char* argv[]) {
    char *bitCoinBalancesFile, *transactionsFile;
    int bitCoinValue;
    int senderHashTableNumOfEntries, receiverHashTableNumOfEntries, bucketSize;
    FILE *fp, *fp1;
    /* Create a hashtable for the senders */
    UsersHashTable *senderHashTable, *receiverHashTable;
    WalletHashTable *walletHashTable;
    TreeHashTable *treeHashTable;


    readArgs( argc, argv, bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries,
            receiverHashTableNumOfEntries, bucketSize);


    fp = fopen( bitCoinBalancesFile, "r");
    fp1 = fopen( transactionsFile, "r");

    /* Initialize the HashTables */
    senderHashTable = new UsersHashTable(senderHashTableNumOfEntries, bucketSize);
    receiverHashTable = new UsersHashTable(receiverHashTableNumOfEntries, bucketSize);
    walletHashTable = new WalletHashTable(10);
    treeHashTable = new TreeHashTable(3);

    /* Read the bitcoin balances files */
    readCoinsBalance(fp, bitCoinBalancesFile, bitCoinValue, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);
    readTransactions(fp1, transactionsFile, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);

    char command[200];
    strcpy(command, "start");
    //strcpy(command, "exit");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token, *token1;
    int length;
    int earnings, payments, money;
    char *userId;
    /* Switch for the commands */
    while(strcmp(command, "exit")) {
        read = getline(&line, &len, stdin);
        length = strlen(line);
        if( line[length-1] == '\n' )
            line[length-1] = 0;
        token = strtok(line, " ");
        while ( token != NULL ) {
            /* Let's see our command */
            if(!strcmp(token, "/findEarnings")) {
                token = strtok(NULL, " ");
                userId = token;
                /* Between dates */
                token = strtok(NULL, ":");
                if( token == NULL ) {
                    receiverHashTable->printTransactions(userId);
                    earnings = receiverHashTable->getEarnings(userId);
                    printf("% WalletId: %s Earnings: %d \n", token, earnings);
                }
                else {
                    char *token2 = token;
                    int hour1, minutes1, hour2, minutes2;
                    printf("Hour1: %s\n", token);
                    hour1 = atoi(token);
                    token = strtok(NULL, " ");
                    printf("Minutes1: %s\n", token);
                    minutes1 = atoi(token);
                    token2 = strtok(NULL, " ");
                    token1 = strtok_r(token2, ":", &token2);
                    printf("Hour2: %s\n", token1);
                    hour2 = atoi(token1);
                    token1 = strtok_r(NULL, " ", &token2);
                    printf("Minutes2: %s\n", token1);
                    minutes2 = atoi(token1);
                    earnings = receiverHashTable->getEarnings(userId, hour1, minutes1, hour2, minutes2);
                    printf("% WalletId: %s Earnings: %d \n", userId, earnings);
                }
                printf("%s xxxx\n", token);
            }
            else if(!strcmp(token, "/findPayments")) {
                token = strtok(NULL, " ");
                senderHashTable->printTransactions(token);
                payments = senderHashTable->getEarnings(token);
                printf("% WalletId: %s Payments: %d \n", token, payments);
            }
            else if(!strcmp(token, "/walletStatus")) {
                token = strtok(NULL, " ");
                money = walletHashTable->getBalance(token);
                printf("% WalletId: %s Money: %d \n", token, money);
            }
            else if(!strcmp(token, "exit")) {
                token = strtok(NULL, " ");
                delete walletHashTable;
                delete senderHashTable;
                delete receiverHashTable;
                delete treeHashTable;
                free(bitCoinBalancesFile);
                free(transactionsFile);
                exit(0);
            }
            token = strtok(NULL, " ");
        }
    }
}
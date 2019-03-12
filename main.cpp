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
#include "UserCommands.h"

int main(int argc, char* argv[]) {
    char *bitCoinBalancesFile, *transactionsFile = NULL;
    int bitCoinValue;
    int senderHashTableNumOfEntries, receiverHashTableNumOfEntries, bucketSize;
    FILE *fp = NULL, *fp1 = NULL, *fp2 = NULL;
    /* Create a hashtable for the senders */
    UsersHashTable *senderHashTable = NULL, *receiverHashTable = NULL;
    WalletHashTable *walletHashTable = NULL;
    TreeHashTable *treeHashTable = NULL;

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
    readCoinsBalance(fp, bitCoinBalancesFile, bitCoinValue, receiverHashTable, senderHashTable, walletHashTable,
            treeHashTable);
    readTransactions(fp1, transactionsFile, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);

    char command[200];
    strcpy(command, "start");
    //strcpy(command, "exit");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token = NULL, *token1 = NULL;
    int length;
    int earnings, payments, money;
    char *userId;
    /* Switch for the commands */
    while(strcmp(command, "/exit")) {
        read = getline(&line, &len, stdin);
        length = strlen(line);
        if( line[length-1] == '\n' )
            line[length-1] = 0;
        char *line2 = (char*)malloc(strlen(line) + 1);
        strcpy(line2, line);
        token = strtok(line, " ");
        while ( token != NULL ) {
            /* Let's see our command */
            if(!strcmp(token, "/findEarnings")) {
                token = strtok(NULL, " ");
                userId = token;
                /* Between dates */
                token = strtok(NULL, ":");
                if( token == NULL ) {
                    /* Find Earnings Function */
                    earnings = receiverHashTable->getEarnings(userId);
                    printf("WalletId: %s Earnings: %d \n", userId, earnings);
                    receiverHashTable->printTransactions(userId);
                }
                else {
                    findEarnings(userId, receiverHashTable, token, 0);
                }
            }
            else if(!strcmp(token, "/findPayments")) {
                token = strtok(NULL, " ");
                userId = token;
                token = strtok(NULL, ":");
                if( token == NULL ) {
                    payments = senderHashTable->getEarnings(userId);
                    printf("WalletId: %s Payments: %d \n", userId, payments);
                    senderHashTable->printTransactions(userId);
                }
                else {
                    findEarnings(userId, senderHashTable, token, 1);
                }
            }
            else if(!strcmp(token, "/walletStatus")) {
                token = strtok(NULL, " ");
                money = walletHashTable->getBalance(token);
                printf("% WalletId: %s Money: %d \n", token, money);
            }
            else if(!strcmp(token, "/requestTransaction")) {
                /* Token Contains all the data */
                requestTransaction(token, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);
            }
            else if(!strcmp(token, "/requestTransactions")) {
                char *ret = NULL;
                char ch = ';';
                ret = strchr(line2, ch);
                if(ret != NULL) {
                    printf("It is an stdin string !");
                    requestTransactions(token, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);
                }
                else {
                    token = strtok(NULL, " ");
                    printf("It is a file %s \n", token);
                    fp2 = fopen( token, "r");
                    // requestTransactionsFile(fp2, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);
                }
            }
            else if(!strcmp(token, "/bitCoinStatus")) {
                token = strtok(NULL, " ");
                findBitCoinStatus(token, treeHashTable, bitCoinValue);
            }
            else if(!strcmp(token, "/traceCoin")) {
                token = strtok(NULL, " ");
                treeHashTable->traceCoin(token);
            }
            else if(!strcmp(token, "/exit")) {
                token = strtok(NULL, " ");
                delete walletHashTable;
                receiverHashTable->printUsers();
                delete senderHashTable;
                delete receiverHashTable;
                delete treeHashTable;
                free(line);
                free(bitCoinBalancesFile);
                free(transactionsFile);
                free(line2);
                exit(0);
            }
            token = strtok(NULL, " ");
        }
        free(line2);
    }
}
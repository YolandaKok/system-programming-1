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
    char *token;
    int length;
    /* Switch for the commands */
    while(strcmp(command, "exit")) {
        read = getline(&line, &len, stdin);
        length = strlen(line);
        if( line[length-1] == '\n' )
            line[length-1] = 0;
        token = strtok(line, " ");
        while ( token != NULL ) {
            /* Let's see our command */
            if(strcmp(token, "/findEarnings") == 0) {
                token = strtok(NULL, " ");
                printf("%s %d", token, strlen(token));
                receiverHashTable->printTransactions(token);
            }
            token = strtok(NULL, " ");
        }
    }

    printf("BALANCE %d \n", walletHashTable->getBalance("Antonella"));
    printf("BALANCE %d \n", walletHashTable->getBalance("Ioanna"));
    printf("BALANCE %d \n", walletHashTable->getBalance("Tom"));
    delete walletHashTable;
    delete senderHashTable;
    delete receiverHashTable;
    delete treeHashTable;
    free(bitCoinBalancesFile);
    free(transactionsFile);
}
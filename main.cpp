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
    printf("%s %s %d %d %d %d \n", bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries,
            receiverHashTableNumOfEntries, bucketSize);

    /* Read the bitcoin balances files */
    fp = fopen( bitCoinBalancesFile, "r");
    fp1 = fopen( transactionsFile, "r");

    /* Initialize the HashTables */
    senderHashTable = new UsersHashTable(senderHashTableNumOfEntries, bucketSize);
    receiverHashTable = new UsersHashTable(receiverHashTableNumOfEntries, bucketSize);
    walletHashTable = new WalletHashTable(10);
    treeHashTable = new TreeHashTable(3);

    readCoinsBalance(fp, bitCoinBalancesFile, bitCoinValue, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);
    readTransactions(fp1, transactionsFile, receiverHashTable, senderHashTable, walletHashTable, treeHashTable);

    free(bitCoinBalancesFile);
    free(transactionsFile);


    // receiverHashTable->printTransactions("Antonella");

    treeHashTable->printCoin("934");

    receiverHashTable->printTransactions("Antonella");

    walletHashTable->print("Ioanna");
    //walletHashTable->addToWallet("Ioanna", "123", 30);
    printf("BALANCE %d \n", walletHashTable->getBalance("Antonella"));
    //senderHashTable->printTransactions("Ioanna");
    //CoinNode *node = treeHashTable->getRoot("123");
    //node->print();
    //node->printNodes();
    delete walletHashTable;
    delete senderHashTable;
    delete receiverHashTable;
}
//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "IOUtils.h"
#include "Record.h"
#include "Bucket.h"

int main(int argc, char* argv[]) {
    char *bitCoinBalancesFile, *transactionsFile;
    double bitCoinValue;
    int senderHashTableNumOfEntries, receiverHashTableNumOfEntries, bucketSize;
    FILE *fp, *fp1;

    readArgs( argc, argv, bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries, receiverHashTableNumOfEntries,
            bucketSize);
    printf("%s %s %lf %d %d %d \n", bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries,
            receiverHashTableNumOfEntries, bucketSize);

    /* Read the bitcoin balances files */
    fp = fopen( bitCoinBalancesFile, "r");
    //fp1 = fopen( transactionsFile, "r");

    readCoinsBalance(fp, bitCoinBalancesFile);
    //readTransactions(fp1, transactionsFile);

    free(bitCoinBalancesFile);
    free(transactionsFile);

    Bucket *bucket = new Bucket(200);
    bucket->sizeInBytes();
    delete bucket;
}
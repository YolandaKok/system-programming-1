//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "IOUtils.h"
#include "Record.h"
#include "Bucket.h"
#include "DataBucket.h"
#include "Record.h"
#include "SenderHashTable.h"

int main(int argc, char* argv[]) {
    char *bitCoinBalancesFile, *transactionsFile;
    double bitCoinValue;
    int senderHashTableNumOfEntries, receiverHashTableNumOfEntries, bucketSize;
    FILE *fp, *fp1;
    /* Create a hashtable for the senders */
    SenderHashTable *senderHashTable;

    readArgs( argc, argv, bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries, receiverHashTableNumOfEntries,
            bucketSize);
    printf("%s %s %lf %d %d %d \n", bitCoinBalancesFile, transactionsFile, bitCoinValue, senderHashTableNumOfEntries,
            receiverHashTableNumOfEntries, bucketSize);

    /* Read the bitcoin balances files */
    fp = fopen( bitCoinBalancesFile, "r");
    fp1 = fopen( transactionsFile, "r");

    senderHashTable = new SenderHashTable(senderHashTableNumOfEntries, bucketSize);

    readCoinsBalance(fp, bitCoinBalancesFile);
    readTransactions(fp1, transactionsFile, senderHashTable);

    free(bitCoinBalancesFile);
    free(transactionsFile);

    /* Bucket *bucket = new Bucket(bucketSize);
    bucket->addUser("Maria");
    bucket->addUser("Eleni");
    bucket->addUser("Dimitra");
    bucket->addUser("Yorgos");
    bucket->addUser("Thanasis");
    bucket->addUser("Kostas");

    bucket->printUsers(); */

    /*void *records = (void*)malloc(bucketSize);
    Record record1;
    strcpy(record1.name, "Maria");
    memcpy(records, &record1, sizeof(Record));
    Record record2;
    memcpy(&record2, records, sizeof(Record));
    printf("%s \n", record2.name);
    int offset = sizeof(Record);
    Record record3, record4, record5;

    strcpy(record3.name, "Eleni");
    memcpy(records + offset, &record3, sizeof(Record));
    offset += sizeof(Record);

    strcpy(record4.name, "Katerina");
    memcpy(records + offset, &record4, sizeof(Record));
    offset += sizeof(Record);

    memcpy(&record2, records + 100, sizeof(Record));
    printf("%s \n", record2.name);*/

    //delete bucket;
}
//
// Created by yolanda on 28/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "SenderHashTable.h"
#include "Bucket.h"

SenderHashTable::SenderHashTable(int size, int bytes) {
    int i;
    this->size = size;
    this->bucketSize = bytes;
    /* Memory Allocation for the array of pointers' to buckets */
    this->buckets = (Bucket**)malloc(sizeof(Bucket*) * size);
    /* Initialize with NULL every pointer to bucket */
    for( i = 0; i < this->size; i++ ) {
        this->buckets[i] = NULL;
    }
}

/* Hash Function for strings */
int SenderHashTable::hashFunction(char *userId) {
    unsigned long hash = 5381;
    int c;

    while (c = *userId++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % this->size;
}

/* Add The transaction to the right bucket */
int SenderHashTable::addTransaction(Transaction *transaction) {
    int i = hashFunction(transaction->getSender());
    /* Find or insert the user */
    /* Let's see if a list of buckets exists */
    if(this->buckets[i] == NULL) {
        /* Create a new bucket */
        this->buckets[i] = new Bucket(this->bucketSize);
        /* Add User to the bucket */
        this->buckets[i]->addUser(transaction->getSender());
    }
    else {
        /* Add User to the bucket */
        this->buckets[i]->addUser(transaction->getSender());
    }
}

/* Insert the sender and the transaction */
void insertSender(char *sender) {
    /* Hash the value */
    /* If you don't find the sender in the list */
    /* Add it to the last position */
}

/* Destructor for this class */
SenderHashTable::~SenderHashTable() {
    int i = 0;
    /* Deallocate memory for the buckets array */
    for( i = 0; i < this->size; i++ ) {
        if(this->buckets[i] != NULL) {
            // delete this->buckets[i];
            Bucket *current, *temp;
            current = this->buckets[i];
            while( current != NULL ) {
                temp = current->getNext();
                delete current;
                current = temp;
            }
        }
    }
    free(this->buckets);
}
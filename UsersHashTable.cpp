//
// Created by yolanda on 28/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "UsersHashTable.h"
#include "Bucket.h"

UsersHashTable::UsersHashTable(int size, int bytes) {
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
int UsersHashTable::hashFunction(char *userId) {
    unsigned long hash = 5381;
    int c;

    while (c = *userId++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % this->size;
}

void UsersHashTable::traverseTransactions(char *user, Transaction *transaction, WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    int i = hashFunction(user);
    /* If the user exists go to the next */
    if( this->buckets[i]->findUser(user) == 1 ) {
        this->buckets[i]->traverseTransactions(user, transaction, this, walletHashTable, treeHashTable);
    }
}

/* Add The transaction to the right bucket */
int UsersHashTable::addTransaction(char *user, Transaction *transaction) {
    int i = hashFunction(user);
    /* Find or insert the user */
    /* Let's see if a list of buckets exists */
    if(this->buckets[i] == NULL) {
        /* Create a new bucket */
        this->buckets[i] = new Bucket(this->bucketSize);
        /* Add User to the bucket */
        this->buckets[i]->addUser(user, transaction);
    }
    else {
        /* Find if the user exists */
        /* If it does not exists */
        if(this->buckets[i]->findUser(user) == 0) {
            /* Add User to the bucket and First Transaction to the DataBucket */
            this->buckets[i]->addUser(user, transaction);
        }
        else {
            /* Add Transaction to the bucket */
            this->buckets[i]->addTransaction(user, transaction);
        }
    }
    //printf("%d found\n", this->buckets[i]->findUser(transaction->getSender()));
}

void UsersHashTable::printTransactions(char *userId) {
    int hash = hashFunction(userId);
    this->buckets[hash]->printTransactions(userId);
}

void UsersHashTable::printTransactions(char* userId, int hour1, int minutes1, int hour2, int minutes2) {
    int hash = hashFunction(userId);
    this->buckets[hash]->printTransactions(userId, hour1, minutes1, hour2, minutes2);
}

void UsersHashTable::printTransactions(char* userId, int hour1, int minutes1, int day1, int month1, int year1,
        int hour2, int minutes2, int day2, int month2, int year2) {
    int hash = hashFunction(userId);
    this->buckets[hash]->printTransactions(userId, hour1, minutes1, day1, month1, year1, hour2, minutes2, day2,
            month2, year2);
}

int UsersHashTable::getEarnings (char *userId) {
    int hash = hashFunction(userId);
    return this->buckets[hash]->getEarnings(userId);
}

int UsersHashTable::getEarnings (char *userId, int hour1, int minutes1, int hour2, int minutes2) {
    int hash = hashFunction(userId);
    printf("HASH HOUR DAY %s %d", userId, hash);
    return this->buckets[hash]->getEarnings(userId, hour1, minutes1, hour2, minutes2);
}

int UsersHashTable::getEarnings (char *userId, int hour1, int minutes1, int day1, int month1, int year1, int hour2,
        int minutes2, int day2, int month2, int year2) {

    int hash = hashFunction(userId);
    return this->buckets[hash]->getEarnings(userId, hour1, minutes1, day1, month1, year1, hour2, minutes2, day2,
            month2, year2);
}

void UsersHashTable::printUsers() {
    int i;
    for ( i = 0; i < this->size; i++ ) {
        if(this->buckets[i] != NULL)
            this->buckets[i]->printUsers();
    }
}

/* Insert the sender and the transaction */
void insertSender(char *sender) {
    /* Hash the value */
    /* If you don't find the sender in the list */
    /* Add it to the last position */
}

/* Destructor for this class */
UsersHashTable::~UsersHashTable() {
    int i = 0;
    Bucket *current, *temp;
    /* Deallocate memory for the buckets array */
    for( i = 0; i < this->size; i++ ) {
        if(this->buckets[i] != NULL) {
            // delete this->buckets[i];
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
//
// Created by yolanda on 26/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Bucket.h"
#include "DataBucket.h"
#include "Transaction.h"

/* Constructor of a bucket */
Bucket::Bucket(int bytes) {
    this->records = (char*)malloc(bytes);
    this->remainingBytes = bytes;
    this->offset = 0;
    this->next = NULL;
}

int Bucket::sizeInBytes() {

}

/* Transaction will be added to the DataBucket */
int Bucket::addUser(char *name, Transaction *transaction) {
    if(offset + sizeof(DataBucket) < this->remainingBytes) {
        DataBucket dataBucket;
        dataBucket.setName(name);
        dataBucket.setTransactionListHead(transaction);

        memcpy(this->records + offset, &dataBucket, sizeof(DataBucket));
        this->offset += sizeof(DataBucket);
    }
    else {
        if( this->next == NULL ) {
            this->next = new Bucket(this->remainingBytes);
            this->next->addUser(name, transaction);
        }
        else {
            this->next->addUser(name, transaction);
        }
    }
}

void Bucket::printTransactions(char *userId) {
    DataBucket dataBucket;
    int found = 0;
    /* Search Into the Buckets */
    Bucket *current = this;
    while( current != NULL ) {
        int off = 0;
        while ( off < this->offset ) {
            memcpy(&dataBucket, this->records + off, sizeof(DataBucket));
            /* We can see if it is the current name */
            if(strcmp(userId, dataBucket.getName()) == 0) {
                found = 1;
                // Print the list of the transactions
                dataBucket.printTransactions();
                break;
            }
            off += sizeof(DataBucket);
        }
        if(found)
            break;
        current = current->getNext();
    }
    printf("%d alalla \n", found);
    //return found;
}

void Bucket::traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
        WalletHashTable *walletHashTable) {
    /*  */
    DataBucket dataBucket;
    int found = 0;
    /* Search Into the Buckets */
    Bucket *current = this;
    while( current != NULL ) {
        int off = 0;
        while ( off < this->offset ) {
            memcpy(&dataBucket, this->records + off, sizeof(DataBucket));
            /* We can see if it is the current name */
            if(strcmp(user, dataBucket.getName()) == 0) {
                dataBucket.traverseTransactions(user, transaction, receiverHashTable, walletHashTable);
                found = 1;
                break;
            }
            off += sizeof(DataBucket);
        }
        if(found)
            break;
        current = current->getNext();
    }
    // return found;
}

int Bucket::addTransaction(char *user, Transaction *transaction) {
    /* Add Transaction To the Transactions List */
    DataBucket dataBucket;
    int found = 0;
    /* Search Into the Buckets */
    Bucket *current = this;
    while( current != NULL ) {
        int off = 0;
        while ( off < current->offset ) {
            memcpy(&dataBucket, current->records + off, sizeof(DataBucket));
            /* We can see if it is the current name */
            // printf("%s %s!!!!! \n", user, dataBucket.getName());
            if(strcmp(user, dataBucket.getName()) == 0) {
                // printf("Found \n");
                // Add to the transaction list of this DataBucket for this user
                dataBucket.addTransaction(dataBucket.getTransactionListHead(), transaction);
                found = 1;
                break;
            }
            off += sizeof(DataBucket);
        }
        if(found)
            break;
        current = current->next;
    }
}

/* Returns true or false */
int Bucket::findUser(char *name) {
    DataBucket dataBucket;
    int found = 0;
    /* Search Into the Buckets */
    Bucket *current = this;
    while( current != NULL ) {
        int off = 0;
        while ( off < this->offset ) {
            memcpy(&dataBucket, this->records + off, sizeof(DataBucket));
            /* We can see if it is the current name */
            if(strcmp(name, dataBucket.getName()) == 0) {
                found = 1;
                break;
            }
            off += sizeof(DataBucket);
        }
        if(found)
            break;
        current = current->getNext();
    }
    return found;
}

/*int Bucket::addTransaction(char *name, Transaction *transaction) {
    /* Find if user exists into the buckets */

    /* If it exists insert the transaction into this */
    /* If it does not exist make a new DataBucket */
//}

/* Traverse the buckets' list */
void Bucket::printUsers() {
    /* Print all the users */
    DataBucket dataBucket;
    int off = 0;
    while (off < this->offset) {
        memcpy(&dataBucket, this->records + off, sizeof(DataBucket));
        dataBucket.printName();
        off += sizeof(DataBucket);
    }
    if(this->next != NULL) {
        this->next->printUsers();
    }
}

Bucket* Bucket::getNext() {
    return this->next;
}

Bucket::~Bucket() {
    /* For every DataBucket Delete The Transactions List */
    DataBucket dataBucket;
    int found = 0;
    /* Search Into the Buckets */
    Bucket *current = this;
    while( current != NULL ) {
        int off = 0;
        while ( off < current->offset ) {
            memcpy(&dataBucket, current->records + off, sizeof(DataBucket));
            dataBucket.removeTransactions();
            /* We can see if it is the current name */
            off += sizeof(DataBucket);
        }
        current = current->next;
    }
    free(this->records);
}


//
// Created by yolanda on 26/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Bucket.h"
#include "DataBucket.h"

/* Constructor of a bucket */
Bucket::Bucket(int bytes) {
    this->records = (char*)malloc(bytes);
    this->remainingBytes = bytes;
    this->offset = 0;
    this->next = NULL;
}

int Bucket::sizeInBytes() {

}

int Bucket::addUser(char *name) {
    if(offset + sizeof(DataBucket) < this->remainingBytes) {
        DataBucket dataBucket;
        dataBucket.setName(name);

        memcpy(this->records + offset, &dataBucket, sizeof(DataBucket));
        this->offset += sizeof(DataBucket);
    }
    else {

        if( this->next == NULL ) {
            this->next = new Bucket(this->remainingBytes);
            this->next->addUser(name);
        }
        else {

            this->next->addUser(name);
        }
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
            printf("%s %s!!!!! \n", name, dataBucket.getName());
            if(strcmp(name, dataBucket.getName()) == 0) {
                printf("Found \n");
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
    printf("%d offset \n", this->offset);
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
    free(this->records);
    /* Delete all the buckets recursively */
}
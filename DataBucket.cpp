//
// Created by yolanda on 27/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "DataBucket.h"



DataBucket::DataBucket() {

}

DataBucket::DataBucket(char name[50]){
    strcpy(this->name, name);
}

void DataBucket::setName(char name[50]) {
    strcpy(this->name, name);
}

/* Set the head of the transaction head */
void DataBucket::setTransactionListHead(Transaction *transaction) {
    this->head = transaction;
}

/* Add Transaction to the DataBucket */
void DataBucket::addTransaction(Transaction *head, Transaction *transaction) {
    head->setNext(head, transaction);
}

void DataBucket::traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
        WalletHashTable *walletHashTable) {
    this->head->traverseTransactions(user, transaction, receiverHashTable, walletHashTable);
}

Transaction* DataBucket::getTransactionListHead() {
    return this->head;
}

char* DataBucket::getName() {
    return this->name;
}

void DataBucket::printName() {
    printf("%s NAME \n", this->name);
}

void DataBucket::removeTransactions() {
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        temp = current->getNext();
        delete current;
        current = temp;
    }
}

void DataBucket::printTransactions() {
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        //if(!current->getVirtualTransaction()) {
            printf("Sender: %s, Receiver: %s, Amount: %d, Id: %s \n", current->getSender(), current->getReceiver(),
                   current->getAmount(), current->getTransactionId());
        //}
        current = current->getNext();
    }
}

/* Remove transactions from the DataBucket */
DataBucket::~DataBucket() {

}

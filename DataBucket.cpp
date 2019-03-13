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
        WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {
    this->head->traverseTransactions(user, transaction, receiverHashTable, walletHashTable, treeHashTable);
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
    this->head = NULL;
}


void DataBucket::printTransactions() {
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction()) {
            printf("Sender: %s, Receiver: %s, Amount: %d, Id: %s \n", current->getSender(), current->getReceiver(),
                   current->getAmount(), current->getTransactionId());
        }
        current = current->getNext();
    }
}

void DataBucket::printTransactions(int day1, int minutes1, int day2, int minutes2) {
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction() && current->getTimeStamp()->isBetweenHour(day1, minutes1, day2, minutes2)) {
        printf("Sender: %s, Receiver: %s, Amount: %d, Id: %s \n", current->getSender(), current->getReceiver(),
               current->getAmount(), current->getTransactionId());
        }
        current = current->getNext();
    }
}


void DataBucket::printTransactions(int hour1, int minutes1, int day1, int month1, int year1, int hour2, int minutes2,
        int day2, int month2, int year2) {
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction() && current->getTimeStamp()->isBetweenDays(hour1, minutes1, day1, month1,
                year1, hour2, minutes2, day2, month2, year2)) {
            printf("Sender: %s, Receiver: %s, Amount: %d, Id: %s \n", current->getSender(), current->getReceiver(),
                   current->getAmount(), current->getTransactionId());
        }
        current = current->getNext();
    }
}


int DataBucket::getEarnings() {
    int earnings = 0;
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction()) {
            earnings += current->getAmount();
        }
        current = current->getNext();
    }
    return earnings;
}

int DataBucket::getEarnings(int hour1, int minutes1, int hour2, int minutes2) {
    int earnings = 0;
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction() && current->getTimeStamp()->isBetweenHour(hour1, minutes1, hour2, minutes2)) {
            earnings += current->getAmount();
        }
        current = current->getNext();
    }
    return earnings;
}

int DataBucket::getEarnings(int hour1, int minutes1, int day1, int month1, int year1, int hour2, int minutes2, int day2,
        int month2, int year2) {
    int earnings = 0;
    Transaction *current = this->head, *temp;
    while( current != NULL ) {
        if(!current->getVirtualTransaction() && current->getTimeStamp()->isBetweenDays(hour1, minutes1, day1, month1,
                year1, hour2, minutes2, day2, month2, year2)) {
            earnings += current->getAmount();
        }
        current = current->getNext();
    }
    return earnings;
}

/* Remove transactions from the DataBucket */
DataBucket::~DataBucket() {

}

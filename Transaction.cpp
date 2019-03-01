//
// Created by yolanda on 28/2/2019.
//

#include "stdio.h"
#include "stdlib.h"
#include <cstring>
#include "Transaction.h"

Transaction::Transaction() {
    this->next = NULL;
}

Transaction::Transaction(char *transactionId, char *sender, char *receiver, int amount) {

}

Transaction* Transaction::getNext () {
    return this->next;
}

void Transaction::setNext(Transaction *head, Transaction *newTransaction) {
    printf("%s new transaction \n", newTransaction->transactionId);
    Transaction *current = head;
    while( current->next != NULL ) {
        current = current->next;
    }
    current->next = newTransaction;
}

/* Getters and Setters */
void Transaction::setTransactionId(char *id) {
    this->transactionId = (char*)malloc(strlen(id) + 1);
    strcpy(this->transactionId, id);
}

void Transaction::setSender(char *sender) {
    this->sender = (char*)malloc(strlen(sender) + 1);
    strcpy(this->sender, sender);
}

char* Transaction::getSender() {
    return this->sender;
}

void Transaction::setReceiver(char *receiver) {
    this->receiver = (char*)malloc(strlen(receiver) + 1);
    strcpy(this->receiver, receiver);
}

void Transaction::setAmount(int amount) {
    this->amount = amount;
}

Transaction::~Transaction() {
    printf("delete transaction %s\n", this->transactionId);
    free(this->receiver); free(this->sender);
    free(this->transactionId);
}
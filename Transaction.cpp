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

void Transaction::traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
        WalletHashTable *walletHashTable) {
    Transaction *current = this;
    //CoinNode *coinNode;
    /* Make the Transaction */
    while( current != NULL ) {
        //coinNode = current->coin;
        if( current->coin->isLeaf() ) {
            printf("%s IDDDD\n", current->coin->getCoinId());
            printf("Insert if Leaf\n");
            /* Let's see if we can insert two CoinNodes */
            CoinNode *coinNode;
            coinNode = current->coin->insertTransaction(transaction);
            /* Add new transaction in the end of this list */
            Transaction *transaction1 = new Transaction();
            transaction1->setCoinNode(coinNode);
            transaction1->setVirtualTransaction(1);
            transaction1->setTransactionId("3");
            transaction1->setSender(transaction->getSender());
            transaction1->setReceiver(transaction->getSender());
            transaction1->setAmount(coinNode->getValue());
            /* Add to the end of the list */
            current->insertLast(transaction1);
            /* Get Left Node */
            CoinNode *left;
            left = current->coin->getLeft();
            /* Insert into the receiverHashTable */
            /* Add Pointer from left coinNode to the transaction */
            left->setTransaction(transaction);
            receiverHashTable->addTransaction(transaction->getReceiver(), transaction);
            /* Put money into the receiver's wallet */
            walletHashTable->addToWallet(transaction->getReceiver(), current->coin->getCoinId(), transaction->getAmount());
            walletHashTable->subtractFromWallet(transaction->getSender(), current->coin->getCoinId(), transaction->getAmount());
            break;
        }
        else {
            current = current->next;
        }
    }
}

void Transaction::insertLast(Transaction *transaction) {
    Transaction *current = this;
    while( current->next != NULL ) {
        current = current->next;
    }
    current->next = transaction;
}

void Transaction::setNext(Transaction *head, Transaction *newTransaction) {
    //printf("%s new transaction \n", newTransaction->transactionId);
    Transaction *current = head;
    while( current->next != NULL ) {
        current = current->next;
    }
    current->next = newTransaction;
}

void Transaction::setCoinNode(CoinNode *coin) {
    this->coin = coin;
}

CoinNode* Transaction::getCoinNode() {
    return this->coin;
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

void Transaction::setVirtualTransaction(int virtualTransaction) {
    this->virtualTransaction = virtualTransaction;
}

char* Transaction::getReceiver() {
    return this->receiver;
}

int Transaction::getAmount() {
    return this->amount;
}

char* Transaction::getTransactionId() {
    return this->transactionId;
}

int Transaction::getVirtualTransaction() {
    return this->virtualTransaction;
}

Transaction::~Transaction() {
    //printf("delete transaction %s\n", this->transactionId);
    free(this->receiver); free(this->sender);
    free(this->transactionId);
}
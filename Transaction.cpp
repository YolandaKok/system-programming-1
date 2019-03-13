//
// Created by yolanda on 28/2/2019.
//

#include "stdio.h"
#include "stdlib.h"
#include <cstring>
#include "Transaction.h"

Transaction::Transaction() {
    this->next = NULL;
    this->head = NULL;
    this->timestamp = NULL;
}

Transaction::Transaction(char *transactionId, char *sender, char *receiver, int amount) {

}

Transaction* Transaction::getNext () {
    return this->next;
}

void Transaction::printTransaction() {
    /* Let's also print the timestamp of the transaction */
    printf("%s %s %s %d", this->transactionId, this->sender, this->receiver, this->amount);
    this->timestamp->print();
}

void Transaction::print() {
    /* Let's also print the timestamp of the transaction */
    printf("%s %s %s %d\n", this->transactionId, this->sender, this->receiver, this->amount);
}

void Transaction::traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
        WalletHashTable *walletHashTable, TreeHashTable *treeHashTable) {

    Transaction *current = this;
    CoinNode *current_coin = this->getCoinNodeListHead();
    int remainder = transaction->getAmount();
    int remainder1;
    transaction->setRemainder(remainder);

    char *t_id;
    t_id = (char*)malloc(strlen("3") + 1);
    strcpy(t_id, "3");

    Transaction *transaction1 = new Transaction();
    /* Make the Transaction */
    while( current != NULL && remainder != 0 ) {
        current_coin = current->getCoinNodeListHead();
        while ( current_coin != NULL && remainder != 0 ) {
            if( current_coin->isLeaf() && (strcmp( current_coin->getOwner(), transaction->getSender() ) == 0) ) {
                /* Let's see if we can insert two CoinNodes */
                CoinNode *coinNode;
                coinNode = current_coin->insertTransaction(transaction);
                /* If it is not NULL the right node */
                if(coinNode != NULL) {
                    /* Add new transaction in the end of this list */
                    //Transaction *transaction1 = new Transaction();
                    if(transaction1->getCoinNodeListHead() == NULL) {
                        transaction1->setCoinNodeListHead(coinNode);
                    }
                    else {
                        transaction1->addCoinNode(coinNode);
                    }
                    transaction1->setVirtualTransaction(1);
                    transaction1->setTransactionId(t_id);
                    transaction1->setSender(transaction->getSender());
                    transaction1->setReceiver(transaction->getSender());
                    transaction1->setAmount(coinNode->getValue());
                    /* Add to the end of the list */
                    current->insertLast(transaction1);
                    /* Get Left Node */
                    CoinNode *left = current_coin->getLeft();
                    /* Insert into the receiverHashTable */
                    /* Add Pointer from left coinNode to the transaction */
                    left->setTransaction(transaction);
                    receiverHashTable->addTransaction(transaction->getReceiver(), transaction);
                    /* Put money into the receiver's wallet */
                    if(walletHashTable->findIfWalletNotFound(transaction->getReceiver()) == 0) {
                        ListNode *list = new ListNode(current_coin->getCoinId(), transaction->getRemainder());
                        walletHashTable->insert(transaction->getReceiver(), list);
                        transaction->setCoinNodeListHead(current_coin->getLeft());
                    } else {
                        walletHashTable->addToWallet(transaction->getReceiver(), current_coin->getCoinId(), transaction->getRemainder());
                    }
                    walletHashTable->subtractFromWallet(transaction->getSender(), current_coin->getCoinId(), transaction->getRemainder());
                    remainder = 0;
                }
                else {
                    /* Let's see if we have a remainder */
                    remainder1 = current_coin->calculateRemainder(transaction);
                    if(transaction->getCoinNodeListHead() == NULL) {
                        transaction->setCoinNodeListHead(current_coin->getLeft());
                    } else {
                        transaction->addCoinNode(current_coin->getLeft());
                    }

                    /* Set Remainder for your transaction */
                    if(walletHashTable->findIfWalletNotFound(transaction->getReceiver()) == 0) {
                        ListNode *list = new ListNode(current_coin->getCoinId(), transaction->getRemainder() - remainder1);
                        walletHashTable->insert(transaction->getReceiver(), list);
                        transaction->setCoinNodeListHead(current_coin->getLeft());
                    } else {
                        walletHashTable->addToWallet(transaction->getReceiver(), current_coin->getCoinId(), transaction->getRemainder() - remainder1);
                    }

                    walletHashTable->subtractFromWallet(transaction->getSender(), current_coin->getCoinId(), transaction->getRemainder() - remainder1);
                    transaction->setRemainder(remainder1);
                    /* Pass CoinNode to the transaction */
                    current_coin = current_coin->getNext();
                    remainder = transaction->getRemainder();
                }
            }
            else {
                current_coin = current_coin->getNext();
            }
        }
        current = current->next;
    }
    free(t_id);
}

void Transaction::setTimestamp(Timestamp *timestamp) {
    this->timestamp = timestamp;
}

void Transaction::setRemainder(int remainder) {
    this->remainder = remainder;
}

int Transaction::getRemainder() {
    return this->remainder;
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

/* Add a new CoinNode */
void Transaction::addCoinNode(CoinNode *coin) {
    CoinNode *current = head;
    //printf("HEADDDD %s \n", head->getCoinId());
    while( current->getNext() != NULL ) {
        current = current->getNext();
    }
    current->setNext(coin);
}

CoinNode* Transaction::getCoinNodeListHead() {
    return this->head;
}

void Transaction::setCoinNodeListHead(CoinNode *head) {
    this->head = head;
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

Timestamp* Transaction::getTimeStamp() {
    return this->timestamp;
}

Transaction::~Transaction() {
    free(this->receiver);
    free(this->sender);
    free(this->transactionId);


    if(this->timestamp != NULL)
        delete this->timestamp;
}
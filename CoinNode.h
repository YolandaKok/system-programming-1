//
// Created by yolanda on 2/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_COINNODE_H
#define SYSTEM_PROGRAMMING_1_COINNODE_H

#include "Transaction.h"

class Transaction;

class CoinNode {
    private:
        char *owner;
        CoinNode *left;
        CoinNode *right;
        int value;
        char *coinId;
        Transaction *transaction;
        CoinNode *next;
    public:
        CoinNode(char *owner, int value, char *coinId);
        void print();
        void printNodes(CoinNode *);
        char* getCoinId();
        CoinNode* getLeft();
        int isLeaf();
        int getValue();
        CoinNode* getNext();
        void setNext(CoinNode *coin);
        int calculateRemainder(Transaction *transaction);
        int findRemainder(Transaction *transaction);
        void setTransaction(Transaction *transaction);
        CoinNode* insertTransaction(Transaction *transaction);
        void deleteTree(CoinNode *root);
        int findUnspent();
        char *getOwner();
        void traceCoin(CoinNode *node);
        int findNumberOfTransactions(CoinNode *root);
        ~CoinNode();
};

#endif //SYSTEM_PROGRAMMING_1_COINNODE_H

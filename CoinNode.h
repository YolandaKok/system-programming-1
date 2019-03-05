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
    public:
        CoinNode(char *owner, int value, char *coinId);
        void print();
        void printNodes();
        char* getCoinId();
        CoinNode* getLeft();
        int isLeaf();
        void insertTransaction(Transaction *transaction);
        ~CoinNode();
};

#endif //SYSTEM_PROGRAMMING_1_COINNODE_H

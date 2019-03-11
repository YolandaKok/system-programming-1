//
// Created by yolanda on 2/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BITCOINTREE_H
#define SYSTEM_PROGRAMMING_1_BITCOINTREE_H

#include "CoinNode.h"

class CoinTree {
    private:
        char *coinId;
        char *initialOwner;
        /* Pointer to the CoinNode */
        CoinNode *root;
        /* Pointer to the next CoinTree */
        CoinTree *next;
    public:
        CoinTree(char *coinId, char *initialOwner, int value);
        /* Insert new Coin */
        CoinNode* insert(char *coinId, char *initialOwner, int value);
        int find(char *coinId);
        void printNodes(char *coinId);
        CoinNode* getRoot(char *coinId);
        int findUnspent(char *coinId);
        int findNumberOfTransactions(char *coinId);
        void traceCoin(char *coinId);
        CoinTree* getNext();
        void setRoot(char *owner, int value, char *coinId);
        void print();
        ~CoinTree();
};

#endif //SYSTEM_PROGRAMMING_1_BITCOINTREE_H

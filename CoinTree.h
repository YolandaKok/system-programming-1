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
        CoinTree(char *coinId, char *initialOwner);
        /* Insert new Coin */
        int insert(char *coinId, char *initialOwner);
        int find(char *coinId);
        CoinTree* getNext();
        void print();
        ~CoinTree();
};

#endif //SYSTEM_PROGRAMMING_1_BITCOINTREE_H

//
// Created by yolanda on 4/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H
#define SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H

#include "CoinTree.h"
#include "CoinNode.h"

class CoinTree;
class CoinNode;

class TreeHashTable {
    private:
        CoinTree **trees;
        int size;
    public:
        TreeHashTable(int size);
        int hashFunction(char *coinId);
        /* Returns 0 if not found, 1 if found */
        CoinNode* insert(char *coinId, char *initialOwner, int value);
        void print();
        void printCoin(char *coinId);
        CoinNode* getRoot(char *coinId);
        int findUnspent(char *coinId);
        int findNumberOfTransactions(char *coinId);
        void traceCoin(char*);
        int findCoin(char *coinId);
        ~TreeHashTable();

};

#endif //SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H

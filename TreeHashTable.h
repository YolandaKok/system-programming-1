//
// Created by yolanda on 4/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H
#define SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H

#include "CoinTree.h"

class TreeHashTable {
    private:
        CoinTree **trees;
        int size;
    public:
        TreeHashTable(int size);
        int hashFunction(char *coinId);
        /* Returns 0 if not found, 1 if found */
        int insert(char *coinId, char *initialOwner);
        void print();
        ~TreeHashTable();

};

#endif //SYSTEM_PROGRAMMING_1_TREEHASHTABLE_H

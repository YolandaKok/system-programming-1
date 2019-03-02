//
// Created by yolanda on 2/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BITCOINTREE_H
#define SYSTEM_PROGRAMMING_1_BITCOINTREE_H

#include "CoinNode.h"

class CoinTree {
    private:
        char *coinId;
        CoinNode *root;
    public:
        CoinTree(char *coinId);
        CoinTree();
};

#endif //SYSTEM_PROGRAMMING_1_BITCOINTREE_H

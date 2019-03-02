//
// Created by yolanda on 2/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_COINNODE_H
#define SYSTEM_PROGRAMMING_1_COINNODE_H

class CoinNode {
    private:
        char *owner;
        CoinNode *left;
        CoinNode *right;
        int value;
        char *coinId;
    public:
        CoinNode(char *owner, int value, char *coinId);
        ~CoinNode();
};

#endif //SYSTEM_PROGRAMMING_1_COINNODE_H

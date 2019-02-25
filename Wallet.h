//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_WALLET_H
#define SYSTEM_PROGRAMMING_1_WALLET_H

#include "ListNode.h"
#include <stdio.h>

class Wallet {
    private:
        char* userId;
        ListNode *start;
        double balance;
    public:
        Wallet(ListNode *start);
        int addCoin(char* coin);
        ~Wallet();
};

#endif

//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_WALLET_H
#define SYSTEM_PROGRAMMING_1_WALLET_H
#include "ListNode.h"
#include <stdio.h>

class ListNode;

class Wallet {
    private:
        char* userId;
        Wallet *next;
        /* List to keep the coins */
        ListNode *coins;
        int balance;
    public:
        Wallet(char *userId, ListNode *head);
        int addCoin(char* coin);
        int insert(char *userId, ListNode *head);
        void printCoins(char *userId);
        int getBalance(char* userId);
        Wallet* getNext();
        ~Wallet();
};

#endif

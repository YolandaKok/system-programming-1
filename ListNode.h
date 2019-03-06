//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_LISTNODE_H
#define SYSTEM_PROGRAMMING_1_LISTNODE_H
#include <stdio.h>
#include "Wallet.h"

class Wallet;

class ListNode {
    private:
        ListNode *next;
        char *coin;
        int coinValue;
    public:
        ListNode(char* coin, int coinValue);
        void insert(char* coin, ListNode *head);
        ListNode* getNext();
        void print();
        int getBalance();
        void addToWallet(char *coin, int amount);
        void subtractFromWallet(char *coin, int amount);
        ~ListNode();
};

#endif //SYSTEM_PROGRAMMING_1_LISTNODE_H

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
        Wallet *wallet;
        char* coin;
    public:
        ListNode(char* coin);
        ListNode(char *coin, Wallet *wallet);
        void insert(char* coin, ListNode *head);
        void insert(char* coin, ListNode *head, Wallet *wallet);
        void printWallet(char *userId, ListNode *head);
        void print(ListNode *head);
        ListNode* getNext();
        ~ListNode();
};

#endif //SYSTEM_PROGRAMMING_1_LISTNODE_H

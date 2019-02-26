//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_HASHTABLE_H
#define SYSTEM_PROGRAMMING_1_HASHTABLE_H

#include "ListNode.h"

class HashTable {
    private:
        int size;
        ListNode **lists;
        //Bucket **nodes;
    public:
        HashTable(int size);
        int hashFunction(char *userId);
        void insertUser(char *userId, Wallet *wallet);
        void printUsers();
        void printUsersWallet(char *userId);
        void addWallet(Wallet *wallet);
        ~HashTable();
};

#endif //SYSTEM_PROGRAMMING_1_HASHTABLE_H

//
// Created by yolanda on 4/3/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_WALLETHASHTABLE_H
#define SYSTEM_PROGRAMMING_1_WALLETHASHTABLE_H

#include "ListNode.h"

class WalletHashTable {
    private:
        int size;
        Wallet **wallets;
    public:
        WalletHashTable(int size);
        int hashFunction(char *userId);
        void print(char *userId);
        int insert(char *userId, ListNode *head);
        int getBalance(char *userId);
        void addToWallet(char *userId, char *coin, int amount);
        void subtractFromWallet(char *userId, char *coin, int amount);
        int findIfWalletNotFound(char *userId);
        ~WalletHashTable();
};

#endif //SYSTEM_PROGRAMMING_1_WALLETHASHTABLE_H

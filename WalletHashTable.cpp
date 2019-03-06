//
// Created by yolanda on 4/3/2019.
//
//
// Created by yolanda on 4/3/2019.
//

#include "WalletHashTable.h"
#include "Wallet.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

WalletHashTable::WalletHashTable(int size) {
    int i = 0;
    this->size = size;
    this->wallets = (Wallet**)malloc(sizeof(Wallet*) * size);

    /* Initialize the Tree Nodes with NULL */
    for ( i = 0; i < this->size; i++ ) {
        this->wallets[i] = NULL;
    }
}

/* Insert CoinId */
int WalletHashTable::insert(char *userId, ListNode *head) {
    /* Find the hash */
    int hash = hashFunction(userId);
    if(this->wallets[hash] == NULL) {
        // Create the new list
        this->wallets[hash] = new Wallet(userId, head);
    }
    else {
        // Add a new node to the hashtable
        this->wallets[hash]->insert(userId, head);
    }
}

int WalletHashTable::getBalance(char *userId) {
    int hash = hashFunction(userId);
    this->wallets[hash]->getBalance(userId);
}

/* Add Money to the User Wallet */

void WalletHashTable::addToWallet(char *userId, char *coin, int amount) {
    int hash = hashFunction(userId);
    this->wallets[hash]->addToWallet(userId, coin, amount);
}

/* Subtract Money from the User Wallet */

void WalletHashTable::subtractFromWallet(char *userId, char *coin, int amount) {
    int hash = hashFunction(userId);
    this->wallets[hash]->subtractFromWallet(userId, coin, amount);
}

/* Print Wallet of a user */
void WalletHashTable::print(char *userId) {
    int hash = hashFunction(userId);
    printf("%d print hash \n", hash);
    this->wallets[hash]->printCoins(userId);
}

/* Hash Function for strings */
int WalletHashTable::hashFunction(char *userId) {
    unsigned long hash = 5381;
    int c;

    while (c = *userId++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % this->size;
}

WalletHashTable::~WalletHashTable() {
    Wallet *current, *temp;

    int i = 0;
    for ( int i = 0; i < this->size; i++ ) {
        if( this->wallets[i] != NULL ) {
            current = this->wallets[i];
            while(current != NULL) {
                temp = current->getNext();
                delete current;
                current = temp;
            }
        }
    }
    free(this->wallets);
}
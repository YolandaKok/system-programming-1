//
// Created by yolanda on 24/2/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "Wallet.h"
#include "ListNode.h"
#include <cstring>

Wallet::Wallet(char *userId, ListNode *head) {
    this->coins = head;
    this->next = NULL;
    this->balance = 0;
    this->userId = (char*)malloc(strlen(userId) + 1);
    strcpy(this->userId, userId);
}

int Wallet::addCoin(char *coin) {

}

int Wallet::insert(char *userId, ListNode *head) {
    Wallet *current = this;
    /* Traverse the list to find the last node */
    while( current->next != NULL ) {
        current = current->next;
    }
    /* If not found go to next node */
    current->next = new Wallet(userId, head);
}

int Wallet::findUserWallet(char *userId) {
    int found = 1;
    Wallet *current = this;
    while( current != NULL ) {
        if(strcmp(current->userId, userId) == 0) {
            found = 0;
            break;
        }
        current = current->next;
    }
    return found;
}

Wallet* Wallet::getNext() {
    return this->next;
}

void Wallet::printCoins(char *user) {
    Wallet *current = this;
    while ( current != NULL ) {
        if(strcmp(user, current->userId) == 0) {
            current->coins->print();
            break;
        }
        current = current->next;
    }
}

int Wallet::getBalance(char *user) {
    int balance;
    Wallet *current = this;
    while ( current != NULL ) {
        if(strcmp(user, current->userId) == 0) {
            balance = current->coins->getBalance();
            break;
        }
        current = current->next;
    }
    return balance;
}

void Wallet::addToWallet(char *user, char *coin, int amount) {
    /* Traverse the list of coins */
    /* If you find it just + */
    /* If you don't find it add a new list node with this coin */
    Wallet *current = this;
    while ( current != NULL ) {
        if(strcmp(user, current->userId) == 0) {
            current->coins->addToWallet(coin, amount);
            break;
        }
        current = current->next;
    }
}

void Wallet::subtractFromWallet(char *user, char *coin, int amount) {
    Wallet *current = this;
    while ( current != NULL ) {
        if(strcmp(user, current->userId) == 0) {
            current->coins->subtractFromWallet(coin, amount);
            break;
        }
        current = current->next;
    }
}

Wallet::~Wallet() {
    /* Delete the next */
    ListNode *current = this->coins, *temp;
    //current = this;
    while(current != NULL) {
        temp = current->getNext();
        delete current;
        current = temp;
    }
    free(this->userId);
}
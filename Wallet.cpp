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
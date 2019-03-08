//
// Created by yolanda on 24/2/2019.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Wallet.h"
#include "ListNode.h"

ListNode::ListNode(char* coin, int coinValue) {
    //this->coin = coin;
    this->coin = (char*)malloc(strlen(coin) + 1);
    strcpy(this->coin, coin);
    this->next = NULL;
    this->coinValue = coinValue;
}

void ListNode::insert(char* coin, ListNode *head) {
    ListNode *current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = new ListNode(coin, current->coinValue);
}

int ListNode::getBalance() {
    int balance = 0;
    ListNode *current = this;
    while( current != NULL ) {
        balance += current->coinValue;
        current = current->next;
    }
    return balance;
}

void ListNode::addToWallet(char *coin, int amount) {
    int found = 0;
    /* Add to the wallet */
    ListNode *current = this;
    while( current->next != NULL ) {
        /* If you find the coin just + into the amount else add a new node to the list */
        if(strcmp(current->coin, coin) == 0) {
            current->coinValue += amount;
            found = 1;
            break;
        }
        current = current->next;
    }
    if(found == 0) {
        current->next = new ListNode(coin, amount);
    }
}

void ListNode::subtractFromWallet(char *coin, int amount) {
    int found = 0;
    /* Add to the wallet */
    ListNode *current = this;
    while( current != NULL ) {
        /* If you find the coin just + into the amount else add a new node to the list */
        if(strcmp(current->coin, coin) == 0) {
            current->coinValue -= amount;
            found = 1;
            break;
        }
        current = current->next;
    }
}

void ListNode::print() {
    ListNode *current = this;
    while( current != NULL ) {
        printf("Coin Id: %s \n", current->coin);
        current = current->next;
    }
}

ListNode* ListNode::getNext() {
    return this->next;
}

ListNode::~ListNode() {
    free(this->coin);
}
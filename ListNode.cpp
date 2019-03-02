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
    this->coin = (char*)malloc((strlen(coin) + 1) * sizeof(char));
    strcpy(this->coin, coin);
    this->next = NULL;
    this->wallet = NULL;
    this->coinValue = coinValue;
}

ListNode::ListNode(char* coin, Wallet *wallet) {
    this->coin = (char*)malloc((strlen(coin) + 1) * sizeof(char));
    strcpy(this->coin, coin);
    this->next = NULL;
    this->wallet = wallet;
}

void ListNode::insert(char* coin, ListNode *head) {
    ListNode *current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = new ListNode(coin, current->coinValue);
}

void ListNode::printWallet(char *userId, ListNode *head) {
    ListNode *current = head;
    while(current != NULL) {
        printf("%s userrrr\n", current->coin);
        if(strcmp(current->coin, userId) == 0) {
            current->wallet->printCoins();
            break;
        }
        current = current->next;
    }
}

void ListNode::insert(char *coin, ListNode *head, Wallet *wallet) {
    ListNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new ListNode(coin, current->coinValue);
    current->next->wallet = wallet;
}

void ListNode::print(ListNode *head) {
    ListNode *current = head;
    while(current != NULL) {
        printf("Bitcoin: %s ", current->coin);
        current = current->next;
    }
    //printf("\n");
}

ListNode* ListNode::getNext() {
    return this->next;
}

ListNode::~ListNode() {
    free(this->coin);
    if(this->wallet != NULL) {
        delete this->wallet;
    }
}
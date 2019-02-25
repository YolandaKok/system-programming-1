//
// Created by yolanda on 24/2/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "Wallet.h"
#include "ListNode.h"

Wallet::Wallet(ListNode *head) {
    this->start = head;
}

int Wallet::addCoin(char *coin) {
    this->start->insert(coin, this->start);
}

Wallet::~Wallet() {
    /* Delete the next */
    ListNode *current, *temp;
    current = this->start;
    while(current != NULL) {
        temp = current->getNext();
        delete current;
        current = temp;
    }
}
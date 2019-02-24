//
// Created by yolanda on 24/2/2019.
//

#include "ListNode.h"
#include <stdio.h>

ListNode::ListNode(int coin) {
    this->coin = coin;
    this->next = NULL;
}

void ListNode::insert(int coin, ListNode *head) {
    ListNode *current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = new ListNode(coin);
}

void ListNode::print(ListNode *head) {
    ListNode *current = head;
    while(current != NULL) {
        printf("Bitcoin: %d ", current->coin);
        current = current->next;
    }
    printf("\n");
}
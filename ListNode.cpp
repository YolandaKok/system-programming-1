//
// Created by yolanda on 24/2/2019.
//

#include "ListNode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ListNode::ListNode(char* coin) {
    //this->coin = coin;
    this->coin = (char*)malloc((strlen(coin) + 1) * sizeof(char));
    strcpy(this->coin, coin);
    this->next = NULL;
}

void ListNode::insert(char* coin, ListNode *head) {
    ListNode *current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = new ListNode(coin);
}

void ListNode::print(ListNode *head) {
    ListNode *current = head;
    while(current != NULL) {
        printf("Bitcoin: %s ", current->coin);
        current = current->next;
    }
    printf("\n");
}

ListNode* ListNode::getNext() {
    return this->next;
}

ListNode::~ListNode() {
    free(this->coin);
}
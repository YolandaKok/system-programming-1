//
// Created by yolanda on 25/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Wallet.h"

HashTable::HashTable(int size) {
    int i = 0;
    this->size = size;
    this->lists = (ListNode**)malloc(sizeof(ListNode*) * this->size);
    /* Initialize all the lists */
    for( i = 0; i < this->size; i++ ) {
        this->lists[i] = NULL;
    }
}

void HashTable::insertUser(char *userId, Wallet *wallet) {
    int hash = hashFunction(userId);
    if(this->lists[hash] == NULL) {
        // Create the new list
        this->lists[hash] = new ListNode(userId, wallet);
    }
    else {
        // Add a new node to the hashtable
        this->lists[hash]->insert(userId, this->lists[hash], wallet);
    }
}

void HashTable::printUsers() {
    for( int i = 0; i < this->size; i++ ) {
        printf("Node %d \n", i);
        this->lists[i]->print(this->lists[i]);
    }
}

void HashTable::printUsersWallet(char *userId) {
    int hash = hashFunction(userId);
    printf("%s useridddd \n ", userId);
    //this->lists[hash]->print(this->lists[hash]);
    this->lists[hash]->printWallet(userId, this->lists[hash]);
}

/* Hash Function for strings */
int HashTable::hashFunction(char *userId) {
    unsigned long hash = 5381;
    int c;

        while (c = *userId++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash % this->size;
}

HashTable::~HashTable() {
    int i;

    for( i = 0; i < this->size; i++ ) {
        if(this->lists[i] != NULL) {
            ListNode *current, *temp;
            current = this->lists[i];
            while(current != NULL) {
                temp = current->getNext();
                delete current;
                current = temp;
            }
        }
    }
    free(this->lists);
}
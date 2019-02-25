//
// Created by yolanda on 25/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

HashTable::HashTable(int size) {
    int i = 0;
    this->size = size;
    this->lists = (ListNode**)malloc(sizeof(ListNode*) * this->size);
    /* Initialize all the lists */
    for( i = 0; i < this->size; i++ ) {
        this->lists[i] = NULL;
    }
}

void HashTable::insertUser(char *userId) {
    int hash = hashFunction(userId);
    if(this->lists[hash] == NULL) {
        // Create the new list
    }
    else {
        // Add a new node to the hashtable
    }
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
    free(this->lists);
}
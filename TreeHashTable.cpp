//
// Created by yolanda on 4/3/2019.
//

#include "TreeHashTable.h"
#include "CoinNode.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

TreeHashTable::TreeHashTable(int size) {
    int i = 0;
    this->size = size;
    this->trees = (CoinTree**)malloc(sizeof(CoinTree*) * size);

    /* Initialize the Tree Nodes with NULL */
    for ( i = 0; i < this->size; i++ ) {
        this->trees[i] = NULL;
    }
}

/* Insert CoinId */
CoinNode* TreeHashTable::insert(char *coinId, char *initialOwner, int value) {
    CoinNode *coinNode;
    /* Find the hash */
    int hash = hashFunction(coinId);
    if(this->trees[hash] == NULL) {
        // Create the new list
        this->trees[hash] = new CoinTree(coinId, initialOwner, value);
        coinNode = this->trees[hash]->getRoot(coinId);
    }
    else {
        // Add a new node to the hashtable
        coinNode = this->trees[hash]->insert(coinId, initialOwner, value);
    }
    return coinNode;
}

/* Print the HashTable */
void TreeHashTable::print() {
    int i;
    for( i = 0; i < this->size; i++ ) {
        printf("%d HashTableTree \n", i);
        if( this->trees[i] != NULL ) {
            this->trees[i]->print();
        }
    }
}

/* Find Number of Transactions */
int TreeHashTable::findNumberOfTransactions(char *coinId) {
    int i = hashFunction(coinId);
    this->trees[i]->findNumberOfTransactions(coinId);
}

/* Find Unspent */

int TreeHashTable::findUnspent(char *coinId) {
    int i = hashFunction(coinId);
    this->trees[i]->findUnspent(coinId);
}


void TreeHashTable::traceCoin(char *coinId) {
    int i = hashFunction(coinId);
    this->trees[i]->traceCoin(coinId);
}

CoinNode* TreeHashTable::getRoot(char *coinId) {
    int i = hashFunction(coinId);
    return this->trees[i]->getRoot(coinId);
}

/* Hash Function for strings */
int TreeHashTable::hashFunction(char *userId) {
    unsigned long hash = 5381;
    int c;

    while (c = *userId++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % this->size;
}

TreeHashTable::~TreeHashTable() {
    CoinTree *current, *temp;
    /* Delete every TreeCoin List */
    int i = 0;
    for ( int i = 0; i < this->size; i++ ) {
        if( this->trees[i] != NULL ) {
            current = this->trees[i];
            while(current != NULL) {
                temp = current->getNext();
                delete current;
                current = temp;
            }
        }
    }
    free(this->trees);
}
//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "CoinTree.h"
#include "CoinNode.h"

CoinTree::CoinTree(char *coinId, char *initialOwner) {
    this->coinId = (char*)malloc(strlen(coinId) + 1);
    strcpy(this->coinId, coinId);
    this->initialOwner = (char*)malloc(strlen(initialOwner) + 1);
    strcpy(this->initialOwner, initialOwner);
    /* Initialize the coin id with NULL */
    this->root = NULL;
    this->next = NULL;
}

/* Find if this coinId exists */
/* If found return 1 else return 0 */
int CoinTree::find(char *coinId) {
    int found = 0;
    /* Find CoinId */
    CoinTree *current = this;
    while( current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            found = 1;
            break;
        }
        current = current->next;
    }
    return found;
}

int CoinTree::insert(char *coinId, char *initialOwner) {
    CoinTree *current = this;
    int found = current->find(coinId);
    if(found) {
        return 0;
    }
    else {
        /* Traverse the list to find the last node */
        while( current->next != NULL ) {
            current = current->next;
        }
    }
    /* If not found go to next node */
    current->next = new CoinTree(coinId, initialOwner);
}

void CoinTree::print() {
    /* Print the current list */
    CoinTree *current = this;
    while ( current != NULL ) {
        printf("Coin Id: %s ", current->coinId);
        current = current->next;
    }
    printf("\n");
}

CoinTree* CoinTree::getNext() {
    return this->next;
}

/* Add New Transaction */

// TODO: Delete the current List of CoinTrees
CoinTree::~CoinTree() {
    free(this->coinId);
    free(this->initialOwner);
}
//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "CoinTree.h"
#include "CoinNode.h"

CoinTree::CoinTree(char *coinId, char *initialOwner, int value) {
    this->coinId = (char*)malloc(strlen(coinId) + 1);
    strcpy(this->coinId, coinId);
    this->initialOwner = (char*)malloc(strlen(initialOwner) + 1);
    strcpy(this->initialOwner, initialOwner);
    /* Initialize the coin id with NULL */
    this->root = new CoinNode(initialOwner, value, coinId);
    this->next = NULL;
}

CoinNode* CoinTree::getRoot(char *coinId) {
    CoinTree *current = this;

    /* Traverse the list to find the last node */
    while( current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            break;
        }
        current = current->next;
    }
    return current->root;
}

void CoinTree::setRoot(char *owner, int value, char *coinId){
    this->root = new CoinNode(owner, value, coinId);
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

CoinNode* CoinTree::insert(char *coinId, char *initialOwner, int value) {
    CoinTree *current = this;

    /* Traverse the list to find the last node */
    while( current->next != NULL ) {
        current = current->next;
    }

    /* If not found go to next node */
    current->next = new CoinTree(coinId, initialOwner, value);
    return current->next->root;
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

void CoinTree::printNodes(char *coinId) {
    CoinTree *current = this;
    while (current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            current->root->printNodes(current->root);
            break;
        }
        current = current->next;
    }
}


void CoinTree::traceCoin(char *coinId) {
    CoinTree *current = this;
    while (current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            current->root->traceCoin(current->root);
            break;
        }
        current = current->next;
    }
}


/* Find the number of transactions */
int CoinTree::findNumberOfTransactions(char *coinId){
    int transactions;
    CoinTree *current = this;
    while (current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            transactions = current->root->findNumberOfTransactions(current->root);
            break;
        }
        current = current->next;
    }
    return transactions;
}

int CoinTree::findUnspent(char *coinId) {
    int unspent = 0;
    CoinTree *current = this;
    while (current != NULL ) {
        if(strcmp(current->coinId, coinId) == 0) {
            unspent = current->root->findUnspent();
            break;
        }
        current = current->next;
    }
    return unspent;
}

CoinTree* CoinTree::getNext() {
    return this->next;
}

/* Add New Transaction */

// TODO: Delete the current List of CoinTrees
CoinTree::~CoinTree() {
    free(this->coinId);
    free(this->initialOwner);
    /* Remove the Trees */
    CoinNode *current = this->root;
    current->deleteTree(current);
}
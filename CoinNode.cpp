//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "CoinTree.h"
#include "CoinNode.h"
#include "Transaction.h"

CoinNode::CoinNode(char *owner, int value, char *coinId) {
    this->owner = (char*)malloc(strlen(owner) + 1);
    strcpy(this->owner, owner);
    this->value = value;
    this->coinId = (char*)malloc(strlen(coinId) + 1);
    strcpy(this->coinId, coinId);

    /* Initialize left and right nodes to NULL */
    this->left = NULL;
    this->right = NULL;
}


void CoinNode::print() {
    printf("%s Owner %d amount %s id \n", this->owner, this->value, this->coinId);
}

void CoinNode::printNodes() {
    printf("SAAAAA %s Owner %d Value %s CoinId \n", this->owner, this->value, this->coinId);
    if(this->left == NULL) {
        printf("LEFT NULL \n");
    }
    if(this->right == NULL) {
        printf("RIGHT NULL \n");
    }
    this->left->print();
    this->right->print();
}

CoinNode* CoinNode::getLeft() {
    return this->left;
}

/* Insert Coin Node */
void CoinNode::insertTransaction(Transaction *transaction) {
    /* Insert */
    this->left = new CoinNode(transaction->getReceiver(), transaction->getAmount(), this->coinId);
    //this->left->printNodes();
    /* Node to the right contains */
    if( this->value - transaction->getAmount() > 0) {
        /* Insert Node to the right */
        this->right = new CoinNode(this->owner, this->value - transaction->getAmount(), this->coinId);
    }
}

char* CoinNode::getCoinId() {
    return this->coinId;
}

int CoinNode::isLeaf() {
    if( this->right == NULL && this->left == NULL ) {
        return true;
    }
    else {
        return false;
    }
}

/* Now I have to insert new transaction Node for this bitcoin */



CoinNode::~CoinNode() {
    free(this->owner); free(this->coinId);
}
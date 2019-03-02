//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "CoinTree.h"
#include "CoinNode.h"

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


/* Now I have to insert new transaction Node for this bitcoin */



CoinNode::~CoinNode() {
    free(this->owner); free(this->coinId);
}
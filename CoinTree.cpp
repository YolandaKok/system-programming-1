//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "CoinTree.h"
#include "CoinNode.h"

CoinTree::CoinTree(char *coinId) {
    this->coinId = (char*)malloc(strlen(coinId) + 1);
    strcpy(this->coinId, coinId);
    /* Initialize the coin id with NULL */
    this->root = NULL;
}

/* Add New Transaction */

CoinTree::~CoinTree() {
    free(this->coinId);
}
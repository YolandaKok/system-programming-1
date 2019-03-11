//
// Created by yolanda on 2/3/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
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
    this->transaction = NULL;
    this->next = NULL;
}


CoinNode* CoinNode::getNext() {
    return this->next;
}

void CoinNode::setNext(CoinNode *coin) {
    this->next = coin;
}

void CoinNode::print() {
    if(this->transaction != NULL)
        this->transaction->printTransaction();
}

void CoinNode::printNodes(CoinNode *node) {

    if (node == NULL)
        return;

    /* first print data of node */
    node->print();

    /* then recur on left sutree */
    printNodes(node->left);

    /* now recur on right subtree */
    printNodes(node->right);
}

void CoinNode::traceCoin(CoinNode *node) {

    if (node == NULL)
        return;

    /* first print data of node */
    node->print();

    /* then recur on left sutree */
    printNodes(node->left);

    /* now recur on right subtree */
    printNodes(node->right);
}


int CoinNode::findUnspent() {
    int unspent = this->value;
    int count = 0;
    CoinNode *previous = this;
    CoinNode *current = this->right;
    while( current != NULL ) {
        unspent = current->value;
        previous = current;
        current = current->right;
        count++;
    }
    /*if(this->left != NULL)
        printf("Left: %d\n", this->left->getValue());
    if(this->right != NULL)
        printf("Right: %d\n", this->right->getValue());*/
    if(previous->left != NULL) {
        //printf("%d Previous Left \n", previous->left->getValue());
        unspent = 0;
    }
   // printf("%d COUNT \n", count);
    return unspent;
}

int CoinNode::findNumberOfTransactions(CoinNode *root){
    if(root == NULL){ return 0; }

    if(root->left == NULL)
    {
        // NO Left child.
        return findNumberOfTransactions(root->right);
    }
    else
    {
        // Left child present.
        return findNumberOfTransactions(root->left) + findNumberOfTransactions(root->right) + 1;
    }
}

char* CoinNode::getOwner() {
    return this->owner;
}

CoinNode* CoinNode::getLeft() {
    return this->left;
}

int CoinNode::getValue() {
    return this->value;
}

void CoinNode::setTransaction(Transaction *transaction) {
    this->transaction = transaction;
}

int CoinNode::findRemainder(Transaction *transaction) {
    if( this->value - transaction->getRemainder() < 0 ) {
        return 1;
    }
    return 0;
}

int CoinNode::calculateRemainder(Transaction *transaction) {
    return abs(this->value - transaction->getRemainder());
}

/* Insert Coin Node */
CoinNode* CoinNode::insertTransaction(Transaction *transaction) {
    /* Insert */
    //this->left = new CoinNode(transaction->getReceiver(), transaction->getAmount(), this->coinId);
    //this->left->printNodes();
    /* Node to the right contains */
    if(this->findRemainder(transaction) == 0) {
        /* There is some money left to sent */
        this->left = new CoinNode(transaction->getReceiver(), transaction->getRemainder(), this->coinId);
        if(transaction->getCoinNodeListHead() == NULL) {
            transaction->setCoinNodeListHead(this->left);
        }
        else {
            transaction->addCoinNode(this->left);
        }
        this->left->setTransaction(transaction);
        /* Create a new Transaction to put the unspent */
        /* Insert Node to the right */
        this->right = new CoinNode(this->owner, this->value - transaction->getRemainder(), this->coinId);
    }
    else {
        this->left = new CoinNode(transaction->getReceiver(), this->getValue(), this->coinId);
        this->left->setTransaction(transaction);
        // TODO: Check if it is worth it
        this->right = NULL;
    }
    return this->right;
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

void CoinNode::deleteTree(CoinNode *root) {
    if(root == NULL) {
        return;
    }
    else {
        free(root->owner); free(root->coinId);
        deleteTree(root->left);
        deleteTree(root->right);
    }
    delete root;
}


CoinNode::~CoinNode() {

}
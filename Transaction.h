//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_TRANSACTION_H
#define SYSTEM_PROGRAMMING_1_TRANSACTION_H

#include "CoinNode.h"
#include "UsersHashTable.h"

#include "WalletHashTable.h"

class WalletHashTable;

class UsersHashTable;

class CoinNode;

class Transaction {
    private:
        char *transactionId;
        char *sender;
        char *receiver;
        int amount;
        int virtualTransaction;
        Transaction *next;
        /* List Of CoinNodes in every transaction */
        /* Because we may have used more than one */
        CoinNode *head;
        int remainder;
        // Date // Time make a struct for them
    public:
        Transaction();
        Transaction(char *transactionId, char *sender, char *receiver, int amount);
        /* Getters and Setters */
        void setTransactionId(char *id);
        void setSender(char *sender);
        char* getSender();
        char* getReceiver();
        int getAmount();
        char* getTransactionId();
        void setReceiver(char *receiver);
        void setAmount(int amount);
        void setNext(Transaction *head, Transaction *newTransaction);
        void setVirtualTransaction(int virtualTransaction);
        /* Create a list of CoinNodes */
        void addCoinNode(CoinNode *coin);
        CoinNode* getCoinNodeListHead();
        void setCoinNodeListHead(CoinNode *head);
        void setRemainder(int remainder);
        int getRemainder();
        void insertLast(Transaction *transaction);
        int getVirtualTransaction();
        void traverseTransactions(char *user, Transaction *transaction, UsersHashTable *receiverHashTable,
                WalletHashTable *walletHashTable);
        Transaction* getNext();
        ~Transaction();
};

#endif //SYSTEM_PROGRAMMING_1_TRANSACTION_H

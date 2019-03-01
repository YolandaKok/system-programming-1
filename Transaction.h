//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_TRANSACTION_H
#define SYSTEM_PROGRAMMING_1_TRANSACTION_H

class Transaction {
    private:
        char *transactionId;
        char *sender;
        char *receiver;
        int amount;
        Transaction *next;
        // Date // Time make a struct for them
    public:
        Transaction();
        Transaction(char *transactionId, char *sender, char *receiver, int amount);
        /* Getters and Setters */
        void setTransactionId(char *id);
        void setSender(char *sender);
        char* getSender();
        void setReceiver(char *receiver);
        void setAmount(int amount);
        void setNext(Transaction *head, Transaction *newTransaction);
        Transaction* getNext();
        ~Transaction();
};

#endif //SYSTEM_PROGRAMMING_1_TRANSACTION_H

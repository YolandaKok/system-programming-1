//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BUCKET_H
#define SYSTEM_PROGRAMMING_1_BUCKET_H

class Bucket {
    private:
        char **walletIDs;
        int currentSize;
        /* In bytes */
        int bucketSize;
        Bucket *next;
        /* Pointers to some linked lists */
        Wallet **wallets;
};

#endif //SYSTEM_PROGRAMMING_1_BUCKET_H

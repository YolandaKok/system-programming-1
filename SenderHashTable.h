//
// Created by yolanda on 27/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H
#define SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H

class SenderHashTable {
    private:
        int size;
        Bucket **buckets;
    public:
        SenderHashTable(int size);
        int hashFunction(char *userId);
        /* Add Transaction to the bucket */
        int addTransaction();
        ~SenderHashTable();
};

#endif //SYSTEM_PROGRAMMING_1_SENDERHASHTABLE_H

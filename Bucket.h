//
// Created by yolanda on 26/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BUCKET_H
#define SYSTEM_PROGRAMMING_1_BUCKET_H

class Bucket {
    private:
        void *records;
        Bucket *next;
        int remainingBytes;
        int offset;

    public:
        Bucket(int bytes);
        int sizeInBytes();
        int addUser(char *name);
        Bucket* getNext();
        void printUsers();
        ~Bucket();

};

#endif //SYSTEM_PROGRAMMING_1_BUCKET_H

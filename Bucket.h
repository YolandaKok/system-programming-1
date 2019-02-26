//
// Created by yolanda on 26/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_BUCKET_H
#define SYSTEM_PROGRAMMING_1_BUCKET_H

class Bucket {
    private:
        void *records;
        Bucket *next;
    public:
        Bucket(int bytes);
        int sizeInBytes();
        ~Bucket();

};

#endif //SYSTEM_PROGRAMMING_1_BUCKET_H

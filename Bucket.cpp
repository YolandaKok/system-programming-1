//
// Created by yolanda on 26/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "Bucket.h"

/* Constructor of a bucket */
Bucket::Bucket(int bytes) {
    this->records = (void*)malloc(bytes);
}

int Bucket::sizeInBytes() {

}

Bucket::~Bucket() {
    free(this->records);
}
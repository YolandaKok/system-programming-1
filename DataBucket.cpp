//
// Created by yolanda on 27/2/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "DataBucket.h"

DataBucket::DataBucket() {

}

DataBucket::DataBucket(char name[50]){
    strcpy(this->name, name);
}

void DataBucket::setName(char name[50]) {
    strcpy(this->name, name);
}

char* DataBucket::getName() {
    return this->name;
}

void DataBucket::printName() {
    printf("%s NAME \n", this->name);
}

DataBucket::~DataBucket() {

}

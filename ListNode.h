//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_LISTNODE_H
#define SYSTEM_PROGRAMMING_1_LISTNODE_H

class ListNode {
    private:
        ListNode *next;
        char* coin;
    public:
        ListNode(char* coin);
        void insert(char* coin, ListNode *head);
        void print(ListNode *head);
        ListNode* getNext();
        ~ListNode();
};

#endif //SYSTEM_PROGRAMMING_1_LISTNODE_H

//
// Created by yolanda on 24/2/2019.
//

#ifndef SYSTEM_PROGRAMMING_1_LISTNODE_H
#define SYSTEM_PROGRAMMING_1_LISTNODE_H

class ListNode {
    private:
        ListNode *next;
        int coin;
    public:
        ListNode(int coin);
        void insert(int coin, ListNode *head);
        void print(ListNode *head);
        ~ListNode();
};

#endif //SYSTEM_PROGRAMMING_1_LISTNODE_H

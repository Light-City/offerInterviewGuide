//
// Created by light on 20-2-19.
//
#include <iostream>

struct ListNode {
    int val;
    struct ListNode *next;
};

class Solution {
public:
    ListNode *deleteNode(ListNode *head, int val) {
        if (!head) return NULL;
        if (head->val == val) return head->next;
        head->next = deleteNode(head->next, val);
        return head;
    }
};

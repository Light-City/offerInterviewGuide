//
// Created by light on 20-2-14.
//
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    vector<int> reversePrint(ListNode *head) {
        vector<int> res;
        Recursive(head, res);
        return res;
    }

    void Recursive(ListNode *head, vector<int> &res) {
        if (head == NULL) {
            return;
        }

        Recursive(head->next, res);
        res.push_back(head->val);
    }
};


class Solution1 {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> st;
        while(head) {
            st.push(head->val);
            head=head->next;
        }
        vector<int> res;
        while(!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }
};

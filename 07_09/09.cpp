//
// Created by light on 20-2-15.
//
#include <stack>
#include <iostream>

using namespace std;

class CQueue {
private:
    stack<int> inStack;
    stack<int> outStack;
public:
    CQueue() {
    }

    void appendTail(int value) {
        inStack.push(value);
    }

    int deleteHead() {
        int res = -1;
        if (!outStack.empty()) {
            res = outStack.top();
            outStack.pop();
        } else if (!inStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
            res = outStack.top();
            outStack.pop();
        }
        return res;
    }
};
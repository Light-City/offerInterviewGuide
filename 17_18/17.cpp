//
// Created by light on 20-2-19.
//
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int result = 1;
        int x = 10;

        // 快速幂
        while (n!=0) {
            if(n & 1 == 1) {
                result *= x;
            }
            n >>= 1;
            x *= x;
        }

        for (int i=1;i<result;i++) {
            res.push_back(i);
        }
        return res;
    }
};
//
// Created by light on 20-2-18.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    vector<int> memo = vector<int>(59,-1);
public:
    int cuttingRope(int n) {
        if(n==2)
            memo[2]=1;

        for(int i=1;i<n;i++) {
            int eachFn;
            if(memo[n-i]!=-1)
                eachFn = max(i*(n-i),i*memo[n-i]);
            else
                eachFn = max(i*(n-i),i*cuttingRope(n-i));
            memo[n] = max(memo[n],eachFn);
        }

        return memo[n];
    }

};
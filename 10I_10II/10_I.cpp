//
// Created by light on 20-2-16.
//

class Solution {
private:
    vector<int> dp = vector<int>(101,-1); //最多0~100
public:
    int fib(int n) {
        dp[0]=0;
        dp[1]=1;
        for(int i=2;i<=n;i++) {
            dp[i]=(dp[i-1]+dp[i-2])%1000000007;
        }
        return dp[n];
    }
};
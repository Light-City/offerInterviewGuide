//
// Created by light on 20-2-19.
//

class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double res = 1;

        while(N > 0) {
            // 最后一位是否是1
            if ( (N & 1) == 1) {
                res*=x;
            }
            x *= x;  // 更新2^x
            N = N >> 1;  // 右移一位
        }
        return res;
    }
};
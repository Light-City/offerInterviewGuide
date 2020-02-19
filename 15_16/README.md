# 剑指offer 面试15与16
## 1.[面试题15. 二进制中1的个数](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/)

method1：easy写法，在面试中不可这样做。

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count=0;
        while(n!=0) {
            if((1&n)==1) count++;
            n/=2;
        }
        return count;
    }
};
```

method2：上述n/=2换成位运算n>>1会出问题。分析：对于负数，最高位为1，而负数在计算机是以补码存在的，往右移，符号位不变，符号位1往右移，最终可能会出现全1的情况，导致死循环。与0xffffffff相与，就可以消除负数的影响。与上0xffffffff之后的n是个正数，同负数的补码一样。

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count=0;
        if(n<0) n = n&0xffffffff;
        while(n!=0) {
            count+=1&n;
            n=n>>1;
        }
        return count;
    }
};
```

解决上述问题，还可以用下面方法：

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
         int count = 0;
        int flag = 1;
        while (flag != 0) {
            if ((n & flag) != 0) {
                count++;
            }
            flag = flag << 1;
        }
        return count;
    }
};
```

method3：不存在移位操作，即不存在上述问题，那么可以采用n&(n-1)这样每次都会去掉一个1，上述代码优化为：

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count=0;
        while(n!=0) {
            count++;
            n=n&(n-1);
        }
        return count;
    }
};
```

根据该方法的拓展得到， 判断一个数是否是2的幂

```
bool powerof2(int n)
{
    return ((n & (n-1)) == 0);
}
```

## 2.[面试题16. 数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/)

method1：正负数折半递归，给出的 `n` 可以取到 -2147483648（整型负数的最小值），因此，在编码的时候，需要将 `n` 转换成 `long` 类型。时间复杂度是 O(logN)；由于采用递归结构，空间复杂度是 O(logN)。

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if(n<=0) {
            long long nn =n;
            nn=-nn;
            return 1.0/mp(x,nn);  // 不能直接取-n，会溢出！
        }
        return mp(x,n);
    }
    double mp(double x,long long n) {
        if (n==0) {
            return 1;
        } 
        if(n==1)
            return x;

        double once = myPow(x,n/2);
        if(n%2==0) 
            return once*once;
    
        return x*once*once;
    }
};
```

method2：上述优化

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        if (n == -1) return 1 / x;
        double half = myPow(x,n/2);
        double mod = myPow(x,n%2);
        return half*half*mod;
    }
    
};
```

method3：迭代法，把指数 `n` 做“二进制分解”。例如：1011 = 1x2^3+0x2^2+1X2^1+1x2^0。

系数可以通过右移动获得，2^x次方可以每次右移过程乘以2。在移动过程中只要碰到1，就累乘结果。

时间复杂度O(1) 32位，空间复杂度O(1)。

```cpp
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
```


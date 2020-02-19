# 剑指offer 10-I与10-II

## 1.[面试题10- I. 斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)

method1:递归法

时间复杂度O(n)，空间复杂度O(n)

```
class Solution {
public:
    int fib(int n) {
        if(n==0) 
            return 0;
        if(n==1)
            return 1;
        return (fib(n-1)+fib(n-2))%1000000007;
    }
};
```

method2:基记忆化搜索法

时间复杂度O(n)，空间复杂度O(n)

```
class Solution {
private:
    vector<int> memo = vector<int>(101,-1); //最多0~100
public:
    int fib(int n) {
        memo[0]=0;
        memo[1]=1;
        if(memo[n]==-1)
            memo[n]=(fib(n-1)+fib(n-2))%1000000007;
        return memo[n];
    }
};
```

method3:动态规化法

时间复杂度O(n)，空间复杂度O(n)

```
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
```

method4:动态规化法

时间复杂度O(n)，空间复杂度O(1)

```
class Solution {

public:
    int fib(int n) {
        if(n==0) return 0;
        int f1=0;
        int f2=1;
        for(int i=2;i<=n;i++) {
            int temp=f2;
            f2=(f1+f2)%1000000007;
            f1=temp;
        }   
        return f2;
    }
};
```

## 2.[面试题10- II. 青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

method1:递归法

时间复杂度O(n)，空间复杂度O(n)

```
class Solution {
public:
    int numWays(int n) {
        if(n==0||n==1)
            return 1;
        return (numWays(n-1)+numWays(n-2))%1000000007;
    }
};
```

method2:基记忆化搜索法

时间复杂度O(n)，空间复杂度O(n)

```cpp
class Solution {
private:
    vector<int> memo=vector<int>(101,-1);
public:
    int numWays(int n) {
        if(n==0||n==1) 
            memo[n]=1;
        if(memo[n]==-1) 
            memo[n]=(numWays(n-1)+numWays(n-2))%1000000007;
        return memo[n];
    
    }
};
```

method3:动态规化法

时间复杂度O(n)，空间复杂度O(n)

```cpp
class Solution {
private:
    vector<int> dp = vector<int>(101,-1); //最多0~100
public:
    int numWays(int n) {
        dp[0]=1;
        dp[1]=1;
        for(int i=2;i<=n;i++) {
            dp[i]=(dp[i-1]+dp[i-2])%1000000007;
        }
        return dp[n];
    }
};
```

method4:动态规化法

时间复杂度O(n)，空间复杂度O(1)

```cpp
class Solution {
public:
    int numWays(int n) {
        if(n==0||n==1) return 1;
        int f1=1;
        int f2=1;
        for(int i=2;i<=n;i++) {
            int temp=f2;
            f2=(f1+f2)%1000000007;
            f1=temp;
        }   
        return f2;
    }
};
```



## 3.变态跳台阶

推导：

  f(1) = 1 

  f(2) = f(2-1) + f(2-2)     //f(2-2) 表示2阶一次跳2阶的次数。 

  f(3) = f(3-1) + f(3-2) + f(3-3) 

  ... 

  f(n) = f(n-1) + f(n-2) + f(n-3) + ... + f(n-(n-1)) + f(n-n) 

上述解释：

n = 3时，会有三种跳得方式，1阶、2阶、3阶， 

那么就是第一次跳出1阶后面剩下：f(3-1);第一次跳出2阶，剩下f(3-2)；第一次3阶，那么剩下f(3-3) 

因此结论是f(3) = f(3-1)+f(3-2)+f(3-3)。

当n = n时，会有n中跳的方式，1阶、2阶...n阶，得出结论：

f(n) = f(n-1)+f(n-2)+...+f(n-(n-1)) + f(n-n) => f(0) + f(1) + f(2) + f(3) + ... + f(n-1)

而 f(n-1) = f(0) + f(1)+f(2)+f(3) + ... + f((n-1)-1) = f(0) + f(1) + f(2) + f(3) + ... + f(n-2)，所以：

f(n) = f(0) + f(1) + f(2) + f(3) + ... + f(n-2) +  f(n-1) = f(n-1) + f(n-1) 

 可以得出： 

f(n) = 2*f(n-1)

得出最终结论,在n阶台阶，一次有1、2、...n阶的跳的方式时，总得跳法为： 

​              | 1    ,(n=0 ) 

  f(n) =   | 1    ,(n=1 ) 

​              | 2*f(n-1),(n>=2)

method1:动态规化法

时间复杂度O(n)，空间复杂度O(1)

```cpp
class Solution {
public:
    int jumpFloorII(int number) {
        int f1=1;
        for(int i=2;i<=number;i++) {
            f1=2*f1;
        }
        return f1;
    }
};
```

其余方法同上。

或者更加简单的做法：这青蛙是个神仙（因为他的步长时没限制的），他要做的是从第0个台阶（也就是地面）到第n个，所以第n个是必须踩的，前n-1个踩不踩看心情，都有踩/不踩两种选择，所以时2^(n-1)。

```cpp
class Solution {
public:
    int jumpFloorII(int number) {   
        return pow(2,(number-1));
    }
};
```


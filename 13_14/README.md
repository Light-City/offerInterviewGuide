
# 剑指offer 13与14

## 1.[面试题13. 机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/)

这道题一转换，就是与(0,0)坐标相邻的满足条件的岛。

下面两种算法的时间复杂度与空间复杂度均为O(mxn)。

method1：DFS实现

```cpp
class Solution {
private:
    vector<vector<bool>> isVisited;
    int direct[4][2] = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };
public:
    int movingCount(int m, int n, int k) {
       
        isVisited = vector<vector<bool>>(m,vector<bool>(n,false));
      
        return dfs(0,0,k,m,n);
    }
    int dfs(int x,int y,int k,int m, int n) {
        
        int tmp = rowColSum(x)+rowColSum(y);
        int res=0;
        if(!inArea(m,n,x,y) || isVisited[x][y] || tmp>k) 
            return res;
        
        isVisited[x][y] = true;
        
        res++;

        for(int i=0;i<4;i++) {
            int newX = x+direct[i][0];
            int newY = y+direct[i][1];
            res += dfs(newX,newY,k,m,n);
        }

        return res;
    }
        // 机器人在格子中
    bool inArea(int m,int n,int x,int y) {
        return x>=0 && x<m && y>=0 && y <n;
    }

    int rowColSum(int number) {
        int s=0;
        while(number!=0) {
            s+= number%10;
            number=number/10;
        }
        
        return s;
    }
};
```

对dfs函数上述进行精简：

```cpp
int dfs(int x,int y,int k,int m, int n) {
    int res=0;

    isVisited[x][y] = true;

    res++;
    for(int i=0;i<4;i++) {
        int newX = x+direct[i][0];
        int newY = y+direct[i][1];
        if(inArea(m,n,newX,newY) && !isVisited[newX][newY]  && rowColSum(newX)+rowColSum(newY)<=k)
            res += dfs(newX,newY,k,m,n);
    }

    return res;
}
```

method2：BFS实现

```cpp
class Solution {
private:
    vector<vector<bool>> isVisited;
    int direct[4][2] = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };
public:
    int movingCount(int m, int n, int k) {
        
        isVisited = vector<vector<bool>>(m,vector<bool>(n,false));
        queue<pair<int,int>> q;
        set<pair<int,int>> s;
        q.push(make_pair(0,0));
        while(!q.empty()) {
            auto x_y=q.front();
            int x = x_y.first;
            int y = x_y.second;
            q.pop();
            if (rowColSum(x)+rowColSum(y) <= k && s.count(x_y) == 0 ) {
                s.insert(make_pair(x,y));
                for (int i=0;i<4;i++) {
                    int newX = x + direct[i][0];
                    int newY = y + direct[i][1];
                    if (inArea(m,n,newX,newY)) {
                        q.push(make_pair(newX,newY));
                    }
                }
            }
        }

        return s.size();
    }
   
    // 机器人在格子中
    bool inArea(int m,int n,int x,int y) {
        return x>=0 && x<m && y>=0 && y <n;
    }

    int rowColSum(int number) {
        int s=0;
        while(number!=0) {
            s+= number%10;
            number=number/10;
        }
        
        return s;
    }
};
```

## 2.[面试题14- I. 剪绳子](https://leetcode-cn.com/problems/jian-sheng-zi-lcof/)

method1：递归法，时间复杂度O(n^2)，空间复杂度O(n)。

假设现在绳子长度为n，由题知绳子n>1，最少长度为2，我们假设在长度为n的条件下，得到的最大乘积为F(n)，那么`F(n) = 1*F(n-1)`，依次类推到`F(n) = (n-1)*F(1)`，从而形成类似于斐波那契数列的递归树。这里以`F(n) = 1*F(n-1)`为例，而F(n-1)可以选择不剪也可以选择剪，选择不剪此时`F(n)=1*(n-1)`，选择剪就是根据F(n)一样求F(n-1)，于是便得到一种递归结构。

递归终止条件就是F(2)=1。而每次的`F(n)=max(i*(n-i),i*F(n-i))`。因此递归方法实现如下：

```cpp
class Solution {
public:
    int cuttingRope(int n) {
        if(n==2) return 1;
        int res=-1;  // 隐含F(1) = -1

        for(int i=1;i<n;i++) 
            res = max(res,max(i*(n-i),i*cuttingRope(n-i)));  // 当调用F(1)的时候就是-1

        return res;
    }
   
};
```

method2：记忆化搜索，时间复杂度O(n^2)，空间复杂度O(n)。

在method1中我们得到，递归计算中调用了很多次重复的F(x)，因此我们可以将每次F(x)计算的结果进行存储。

```cpp
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
```

method3：动态规化法，自底向上，先从dp[2]，dp[3]等再往后构建dp[n]。时间复杂度O(n^2)，空间复杂度O(n)。

也就是我们要针对不同绳子长度计算，假设现在绳子长度为i，那么就要计算长度为i的绳子，在1处剪去，2处剪去，再到i-1处剪去所得到的最大值，也就是dp[i]。

因此实现如下：

```cpp
class Solution {
private:
    vector<int> dp;
public:
    int cuttingRope(int n) {
        dp = vector<int>(59,-1);
        dp[2] = 1;

        // 长度为i的绳子从j处开始剪
        for(int i=3;i<=n;i++) {
            for(int j=1;j<i;j++) {
                // 例如F(3) = 1*F(2) 2*F(1)这两种，取最大
                dp[i] = max(dp[i],max(j*(i-j),j*dp[i-j]));
            }
        }
        return dp[n];
    }
   
};
```

method4：贪心法或者说规律法

题目分析：
先举几个例子，可以看出规律来。

```
4 ： 2*2
5 ： 2*3
6 ： 3*3
7 ： 2*2*3 或者4*3
8 ： 2*3*3
9 ： 3*3*3
10：2*2*3*3 或者4*3*3
11：2*3*3*3
12：3*3*3*3
13：2*2*3*3*3 或者4*3*3*3
```

下面是分析：
首先判断F[0]到F[n]可能有哪些数字，实际上只可能是2或者3。
当然也可能有4，但是`4=2*2`，我们就简单些不考虑了。
`5<2*3`，`6<3*3`,比6更大的数字我们就更不用考虑了，肯定要继续分。
其次看2和3的数量，2的数量肯定小于3个，为什么呢？因为`2*2*2<3*3`，那么题目就简单了。
直接用n除以3，根据得到的余数判断是一个2还是两个2还是没有2就行了。
由于题目规定`n>1`，所以2只能是`1*1`，3只能是`2*1`，这两个特殊情况直接返回就行了。

乘方运算的复杂度为：O(log n)，用动态规划来做会耗时比较多。

```cpp
class Solution {

public:
    int cuttingRope(int n) {
        if(n==2) return 1;
        if(n==3) return 2;

        int x = n%3;
        int y = n/3;

        if(x==0) {
            return pow(3,y);
        } else if(x==1) {
            return 2*2*pow(3,y-1);
        }
        return 2*pow(3,y);   
    }
   
};
```

method5：优化版的动态规化，时间复杂度O(n)，空间复杂度O(1)。

在前面method4中分析得到，最大值结果总为1，2，3的组合，且与3的模为0，1，2。因此我们可以只使用长度为3的dp数组进行优化。

```cpp
class Solution {
private:
    vector<int> dp;
public:
    int cuttingRope(int n) {
       dp=vector<int>(3,-1);
       dp[0]=0;
       dp[1]=1;
       dp[2]=1;

       for(int i=3;i<=n;i++) {
           dp[i%3] = max(max((max(dp[(i-1)%3],i-1)),2*max(dp[(i-2)%3],i-2)),3*max(dp[(i-3)%3],i-3));
       }
       return dp[n%3];
    }
};
```

## 3.[面试题14- II. 剪绳子 II](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/)

优先把3用完，贪婪法。

```cpp
class Solution {

public:
    int cuttingRope(int n) {
        if(n==2) return 1;
        if(n==3) return 2;

        long res=1;
        while(n>4) {
            res*=3;
            res=res%1000000007;
            n-=3;
        }   
        return (int)(res*n%1000000007);
    }
   
};
```


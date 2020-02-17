# 剑指offer 11与12

## 1.[面试题11. 旋转数组的最小数字](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)

method1：直接比较，时间复杂度O(n)，空间复杂度O(1)

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
       
        for(int i=1;i<numbers.size();i++) {
            if(numbers[i]<numbers[i-1])
                return numbers[i];
        }
        return numbers[0];
    }
   
};
```

method2：取右边界二分查找法，时间复杂度O(logn)，空间复杂度O(1)。

究竟是取左边界比较，还是右边界比较呢？

取右边界代码好写点，取左边界逻辑类似，下面两者进行对比。

**（1）取右边界。**

对于这个旋转数组，我们知道

- 当取出的mid对应的值小于最右边的值时，说明mid及mid右侧在递增，最小值肯定在mid及其左侧，所以更新右边界为mid。
- 当取出的mid对应的值大于最右边的值时，说明最小值在mid右侧，直接更新左边界为mid+1。
- 当取出的mid对应的值等于最右边的值时，此时就有好2种可能，第一种 2 2 2 1 2 ，第二种 2 1 2 2 2，所以针对这种情况我们只能一步步的逼近，右边界肯定不是最小值，不断往左侧逼近即可，而不能直接取r=mid。

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        // 二分查找法
        int r = numbers.size()-1;
        int l = 0;
        while (l<r) {
            int mid = (r-l) / 2 + l;
            if(numbers[r]>numbers[mid]) {
                r=mid;  // mid可能是最小值,最小值在mid及mid左侧
            } else if(numbers[r]<numbers[mid]) {
                l = mid+1; // 最小值在mid右侧
            } else if(numbers[r]==numbers[mid]) {
                r--; // 最小值不可能是r,可能在mid及mid左侧，也可能在mid及r之间。例如： 2 2 2 1 2 与 2 1 2 2 2。
            }
        }
        return numbers[l];
    }
};
```

method3: 针对上述情况，我们可以得出其递归法。

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        // 二分查找法
        int n = numbers.size()-1;
        
        return minArray(numbers,0,n);
    }
    int minArray(vector<int>& numbers,int left,int right) {
        if (left == right) {
            return numbers[left];
        }
        
        int mid = left + (right-left) / 2;
        if(numbers[mid] > numbers[right]) {
            return minArray(numbers,mid+1,right);
        } else if(numbers[mid] < numbers[right]) {
            return minArray(numbers,left,mid);
        } else {
            return minArray(numbers,left,right-1);
        }
    }
};
```

method4：取左边界二分查找法，时间复杂度O(logn)，空间复杂度O(1)。

**（2）取左边界。**

取左边界就是正常套路呗，一步步分析。

当mid对应的值大于左侧不一定会压缩范围，这是为什么很多人选择第一种取右边界方法的原因。例如：1 3 5这种递增数组，所以如果要采用取左边界方法，就需要排除这种可能，专门针对这种3 4 5 1 2 ,当mid大于左边界与此同时也大于右边界，那么这个方法就可以用了，此时最小值肯定在mid后面，更新l=mid+1。

当mid对应的值小于右边界的时候，最小值肯定在mid及mid左侧，更新右边界r=mid。

当mid对应的值等于右边界的时候，最小值可能在mid左侧也可能在mid右侧，或者本身，例如：2 1 2 2 2 与 2 2 1 2，2 2 2 2，所以一步步向左压缩范围即r--。

当mid对应的值等于左边界的时候，最小值可能在mid左侧也可能在mid右侧，或者本身，例如： 2 1 2 2 2 与 2 2 1 2 ,2 2 2 2，所以一步步向右压缩范围即l++。

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        // 二分查找法
        int r = numbers.size()-1;
        int l = 0;
        while (l<r) {
            int mid = (r-l) / 2 + l;
            if (numbers[mid]>numbers[l] && numbers[mid]>numbers[r]) {
                l = mid+1;
            } else if(numbers[mid]<numbers[r]) {
                r = mid;
            } else if(numbers[mid]==numbers[r]){
                r--;
            } else if(numbers[mid]==numbers[l]) {
                l++;
            }
        }
        return numbers[l];
    }
};
```

method5：取左边界递归法。

而在递归中则有两种写法，一种是按照上述来，

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        // 二分查找法
        int n = numbers.size()-1;
        
        return minArray(numbers,0,n);
    }
    int minArray(vector<int>& numbers,int left,int right) {
        
        if (left==right ) {
            return numbers[left];
        }
        int mid = left + (right-left) / 2;
        // 排除 1 3 5
        if(numbers[mid] > numbers[left] && numbers[mid]>numbers[right]) {
            return minArray(numbers,mid+1,right);
        } else if(numbers[mid] < numbers[right]) {
            return minArray(numbers,left,mid);
        } else if(numbers[mid]==numbers[right]){
            return minArray(numbers,left,right-1);
        } else if(numbers[mid]==numbers[left]) {
            return minArray(numbers,left+1,right);
        }    
        return numbers[left];
    } 
};
```

另一种是在最后相等的时候逼近方法修改为取两段最小值即可。为什么取两段最小值就可以呢，我们把上述最后两种情况挪下来：

当mid对应的值等于右边界的时候，最小值可能在mid左侧也可能在mid右侧，例如：2 1 2 2 2 与 2 2 1 2，所以一步步向左压缩范围即r--。

当mid对应的值等于左边界的时候，最小值可能在mid左侧也可能在mid右侧，例如： 2 1 2 2 2 与 2 2 1 2，所以一步步向右压缩范围即l++。

我们可以看出不管是哪一种，最小值要么在mid左侧，要么在mid右侧，当然也可能是它本身，所以根据这个共性，我们得出取两段最小值即可。

即：

```cpp
 min(minArray(numbers,mid+1,right),minArray(numbers,left,mid))
```

得出如下方案：

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        // 二分查找法
        int n = numbers.size()-1;
        
        return minArray(numbers,0,n);
    }
    int minArray(vector<int>& numbers,int left,int right) {
        
        if (left==right ) {
            return numbers[left];
        }
        int mid = left + (right-left) / 2;
        // 排除 1 3 5
        if(numbers[mid] > numbers[left] && numbers[mid]>numbers[right]) {
            return minArray(numbers,mid+1,right);
        } else if(numbers[mid] < numbers[right]) {
            return minArray(numbers,left,mid);
        }      
        return min(minArray(numbers,mid+1,right),minArray(numbers,left,mid));
    } 
};
```

## 2.[面试题12. 矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)

method1：dfs中直接操作

```cpp
class Solution {
private:
    vector<vector<bool>> isVisited;
    int n,m;
public:
    bool exist(vector<vector<char>>& board, string word) {
        n = board.size();
        if (n==0) return false;
        m = board[0].size();
        isVisited = vector<vector<bool>>(n,vector<bool>(m,false));

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(board[i][j]==word[0])
                    if(dfs(board,word,0,word.length(),i,j))
                        return true;
            }
        }
        return false;
    }
    
    bool inBoard(int x,int y) {
        return x>=0&&x<n&&y>=0&&y<m;
    }
    bool dfs(vector<vector<char>>& board, string word,int start,int end,int x,int y) {

        if(start==end) return true;
        
        if(!inBoard(x,y) || board[x][y]!=word[start]||isVisited[x][y]) return false;

        isVisited[x][y]=true;
        

        int res = dfs(board,word,start+1,end,x+1,y) || dfs(board,word,start+1,end,x-1,y) || dfs(board,word,start+1,end,x,y+1) || dfs(board,word,start+1,end,x,y-1);


        isVisited[x][y] = false;
        return res;
    }
};
```

method2：dfs中使用direct数组。

```cpp
class Solution {
private:
    vector<vector<bool>> isVisited;
    int n,m;
    int direct[4][2] = {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1}
    };
public:
    bool exist(vector<vector<char>>& board, string word) {
        n = board.size();
        if (n==0) return false;
        m = board[0].size();
        isVisited = vector<vector<bool>>(n,vector<bool>(m,false));

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                // 找到单词的第一个字符
                if(board[i][j]==word[0] && !isVisited[i][j]) {
                    isVisited[i][j] = true;
                    if(dfs(board,word,1,word.length(),i,j))
                        return true;
                    isVisited[i][j] = false;
                }
            }
        }
        return false;
    }
    
    bool inBoard(int x,int y) {
        return x>=0&&x<n&&y>=0&&y<m;
    }
    bool dfs(vector<vector<char>>& board, string word,int start,int end,int x,int y) {
        
        if(start==end) return true;
        
        for(int i=0;i<4;i++) {
            int newX = x + direct[i][0];
            int newY = y + direct[i][1];
            if (inBoard(newX,newY) && !isVisited[newX][newY]&&board[newX][newY]==word[start]) {    
                isVisited[newX][newY]=true;
                if(dfs(board,word,start+1,end,newX,newY))
                    return true;
                isVisited[newX][newY]=false;
            } 
        }
        return false;
    }
};
```


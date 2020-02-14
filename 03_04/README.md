# 剑指offer指南

## 1.[面试题03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

method 1: 使用set集合，空间复杂度O(n)，时间复杂度O(n)。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        set<int> s;
        for(auto elem : nums) {
            if (s.count(elem) > 0)
                return elem;
            else 
                s.insert(elem);
        }
        return -1;
    }
};
```

method 2: 使用长度为n的数组，题目中给出每个位置上的元素大小不超过n-1。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        vector<int> v(nums.size(),-1);
        for(auto elem : nums) {
            if(v[elem]!=-1)
                return elem;
            else
                v[elem]++;
        }
        return -1;
    }
};
```

method3: 题目中给出每个位置上的元素大小不超过n-1，所以对于每个元素我们就可以将其放在自己的index上，例如：1放在index=1的位置，遍历所有元素的时候，判断当前元素是否同当前元素已经放在index位置上的元素相同，如果相同，则重复，直接返回，否则不断交换，当元素放到了指定的位置，就往后遍历即可。均摊时间复杂度O(n)，空间复杂度O(1)。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i=0;
        while(i<nums.size()) {
           if(nums[i]==i)
                i++;
            else if(nums[i]==nums[nums[i]])  // 当前元素是否在其index位置上
                return nums[i];
            else {
                swap(nums[i],nums[nums[i]]);
            }
        }
        return -1;
    }
};
```

method4: 先排序，再遍历一遍，时间复杂度O(nlogn)，空间复杂度O(logn)或者O(1)。

STL的sort()算法，数据量大时采用Quick Sort，分段递归排序。一旦分段后的数据量小于某个阈值，为避免Quick Sort的递归调用带来过大的额外开销，就改用Insertion Sort（插入排序）。如果递归层次过深，还会改用Heap Sort。

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        for(int i=1;i<nums.size();i++) {
            if (nums[i]==nums[i-1])
                return nums[i];
        }
        return -1;
    }
};
```

## 2.[面试题04. 二维数组中的查找](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

method1: 右上角或者左下角遍历，时间复杂度O(n+m)，空间复杂度O(1)

```cpp
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if (!n) return false;
        int m = matrix[0].size();

        int i=0,j=m-1;
        while(i<n && j>=0) {
            if(matrix[i][j] == target) {
                return true;
            } else if(matrix[i][j] < target) {
                i++;  
            } else if(matrix[i][j] > target) {
                j--;
            }
        }
        return false;
    }
};
```

method2: 二分查找法，每一行从左到右为递增有序数组，针对每一行使用二分查找，时间复杂度O(nlogm)，空间复杂度O(1)，下述代码做了二分查找的优化，如果`target<matrix[i][mid]`，以后每行都可以不用考虑mid及以后的列。

```cpp
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int l,h,flag=false;
        for(int i=0;i<matrix.size();i++) {
            l=0;
            // 没有进入到target<matrix[i][mid]中,就取每一行全部元素，只要进入了，根据矩阵中元素规则，元素会在mid左边。
            if(!flag) 
                h=matrix[i].size()-1;
            while(l<=h) {
                int mid = (h-l)/2 + l;
                if (target>matrix[i][mid])
                    l=mid+1;
                else if (target<matrix[i][mid]){
                    flag=true;
                    h=mid-1;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
};
```


//
// Created by light on 20-2-14.
//


class Solution {
public:
    // 右上角或者左下角遍历，时间复杂度O(n+m)，空间复杂度O(1)
    bool findNumberIn2DArray1(vector <vector<int>> &matrix, int target) {
        int n = matrix.size();
        if (!n) return false;
        int m = matrix[0].size();

        int i = 0, j = m - 1;
        while (i < n && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] < target) {
                i++;
            } else if (matrix[i][j] > target) {
                j--;
            }
        }
        return false;
    }

    // 二分查找法，每一行从左到右为递增有序数组，针对每一行使用二分查找，
    // 时间复杂度O(nlogm)，空间复杂度O(1)，下述代码做了二分查找的优化，
    // 如果target<matrix[i][mid]，以后每行都可以不用考虑mid及以后的列。
    bool findNumberIn2DArray2(vector <vector<int>> &matrix, int target) {
        int l, h, flag = false;
        for (int i = 0; i < matrix.size(); i++) {
            l = 0;
            // 没有进入到target<matrix[i][mid]中,就取每一行全部元素，只要进入了，根据矩阵中元素规则，元素会在mid左边。
            if (!flag)
                h = matrix[i].size() - 1;
            while (l <= h) {
                int mid = (h - l) / 2 + l;
                if (target > matrix[i][mid])
                    l = mid + 1;
                else if (target < matrix[i][mid]) {
                    flag = true;
                    h = mid - 1;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
};
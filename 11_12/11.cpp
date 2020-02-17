//
// Created by light on 20-2-17.
//
#include <vector>
using namespace std;
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
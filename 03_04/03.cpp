//
// Created by light on 20-2-14.
//

class Solution {
public:
    // 使用set集合，空间复杂度O(n)，时间复杂度O(n)。
    int findRepeatNumber1(vector<int>& nums) {
        set<int> s;
        for(auto elem : nums) {
            if (s.count(elem) > 0)
                return elem;
            else
                s.insert(elem);
        }
        return -1;
    }
    // 使用数组index
    // 使用长度为n的数组，题目中给出每个位置上的元素大小不超过n-1。
    int findRepeatNumber2(vector<int>& nums) {
        vector<int> v(nums.size(),-1);
        for(auto elem : nums) {
            if(v[elem]!=-1)
                return elem;
            else
                v[elem]++;
        }
        return -1;
    }
    // 充分利用题目条件
    /**
     * 题目中给出每个位置上的元素大小不超过n-1，
     * 所以对于每个元素我们就可以将其放在自己的index上，
     * 例如：1放在index=1的位置，遍历所有元素的时候，
     * 判断当前元素是否同当前元素已经放在index位置上的元素相同，
     * 如果相同，则重复，直接返回，否则不断交换，当元素放到了指定的位置，
     * 就往后遍历即可。均摊时间复杂度O(n)，空间复杂度O(1)
     * @param nums
     * @return
     */
    int findRepeatNumber3(vector<int>& nums) {
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
#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/move-zeroes/description/
Difficulty: Medium
Topics: array, two pointers
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroPos = 0;
        for (auto i=0; i<nums.size(); i++) {
            if (nums[i] != 0) {
                nums[zeroPos] = nums[i];
                zeroPos++;
            }
        }
        for (auto j=zeroPos; j<nums.size(); j++) {
            nums[j] = 0;
        }
    }

    void moveZeroesSwap(vector<int>& nums) {
        for (int i=0,next=0; i<nums.size(); ++i)
            if(nums[i])
                swap(nums[i],nums[next++]);
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v;

    cout << "Before operation:" << endl;
    v = {0,1,0,3,12};
    for (auto x: v) cout << x << ",";
    cout << endl;

    cout << "Normal solution:" << endl;
    v = {0,1,0,3,12};
    S->moveZeroes(v);
    for (auto x: v) cout << x << ",";
    cout << endl;

    cout << "STL Swap solution:" << endl;
    v = {0,1,0,3,12};
    S->moveZeroesSwap(v);
    for (auto x: v) cout << x << ",";
    cout << endl;
}

#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/binary-search/description/
Difficulty: Easy
Topics: array, binary search
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        int midnum;

        while (left <= right) {
            mid = left + (right - left) / 2;
            midnum = nums[mid];
            if (midnum == target) {
                return mid;
            } else if (midnum < target) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }

        return -1;
    }
};

int main() {
    vector<int> v = {-1, 0, 3, 5, 9, 12};
    Solution *S = new Solution();
    cout << S->search(v, 9) << endl;
    cout << S->search(v, 2) << endl;
}

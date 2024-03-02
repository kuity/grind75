#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/sort-colors/description/
Difficulty: Medium
Topics: array, two pointers, sorting
*/
class Solution {
private:
    int zeroIndex;
    int twoIndex;

public:
    // Maintain 2 indices, zeroIndex and twoIndex, which respectively increments and decrements
    // As well as an incrementing index for iteration
    // If encounter a 1, can just increment and continue
    void sortColors(vector<int>& nums) {
	zeroIndex = 0;
	twoIndex = nums.size()-1;

	int nextIndex = 0;
	while (nextIndex <= twoIndex) {
	    for (auto x: nums) { cout << x << ","; } cout << endl;
	    auto num = nums[nextIndex];
	    if (num == 0) {
		if (nextIndex == zeroIndex) { // matching then proceed in lock-step
		    zeroIndex++;
		    nextIndex++;
		} else { // not matching then swap and re-process
		    nums[nextIndex] = nums[zeroIndex];
		    nums[zeroIndex] = 0;
		    zeroIndex++;
		}
	    } else if (num == 2) {
		// not matching then swap and re-process
		nums[nextIndex] = nums[twoIndex];
		nums[twoIndex] = 2;
		twoIndex--;
	    } else { // It's a 1, just continue
		nextIndex++;
	    }
	}
    }
};

int main() {
    vector<int> nums = {2,0,2,1,1,0};
    Solution *S = new Solution();
    S->sortColors(nums);
    for (auto x: nums) { cout << x << ","; } cout << endl;
}

#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/search-in-rotated-sorted-array/description/
Difficulty: Medium
Topics: array, binary search
*/
class Solution {
public:
    /*
     * 1. Find the rotation point in O(log n)
     * How? we take A[0], the pivot point must be < A[0]
     * We take A[n/2]. If > A[0], pivot point must be on the right
     * If < A[0], pivot point is on the left. Then can keep searching.
     * 2. check target T > A[p]? Yes, bsearch left array. No, bsearch right array
     *
     * More efficient soln (check LC)
     * No need to find pivot, can directly apply binSearch as one half of the array
     * will always be sorted
    */
    int binSearch(vector<int> & nums, int target, int left, int right) {
	int mid;
	int midnum;

	while (left <= right) {
	    mid = (right + left) / 2;
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


    int findPivot(vector<int>& nums) {
	int pivotRight = nums[0];

	int left = 0;
	int right = nums.size()-1;
	while (left <= right) {
	    int mid = (left + right) / 2;
	    int midVal = nums[mid];
	    if (midVal >= pivotRight) {
		left = mid+1;
	    } else {
		if (mid > 0 && nums[mid-1] > midVal) {
		    return mid;
		}
		right = mid-1;
	    }
	}
	return -1; // no pivot found
    }

    int search(vector<int>& nums, int target) {
	int pivotIndex = findPivot(nums);
	if (pivotIndex == -1) {
	    return binSearch(nums, target, 0, nums.size()-1);
	} else {
	    int first = nums[0];
	    if (target >= first) {
		return binSearch(nums, target, 0, pivotIndex-1);
	    } else {
		return binSearch(nums, target, pivotIndex, nums.size()-1);
	    }
	}
    }
};

int main() {
    vector<int> v = {4, 5, 6, 7, 0, 1, 2};
    Solution *S = new Solution();
    vector<int> v2  = {-50, -20, 5, 10, 11, 40};
    vector<int> v3 = {-20, 5, 10, 11, 40, 55, 60, -31};
    vector<int> v4 = {3,1};
    cout << "check find pivot: " << S->findPivot(v) << endl;
    cout << "check find pivot: " << S->findPivot(v2) << endl;
    cout << "check find pivot: " << S->findPivot(v3) << endl;
    cout << "check find pivot: " << S->findPivot(v4) << endl;
    cout << "check search: " << S->search(v, 1) << endl;
    cout << "check search: " << S->search(v2, 6) << endl;
    cout << "check search: " << S->search(v3, -20) << endl;
    cout << "check search: " << S->search(v4, 1) << endl;
}

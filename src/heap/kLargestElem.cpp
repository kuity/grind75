#include <functional>
#include <queue>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/kth-largest-element-in-an-array/description/
Difficulty: Medium
Topics: array, sorting, heap, quickselect
*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> Q;
        for (auto i=0; i<k; i++) Q.push(nums[i]);
        for (auto i=k; i<nums.size(); i++) {
            auto num = nums[i];
            if (num > Q.top()) {
                Q.pop();
                Q.push(num);
            }
        }
        return Q.top();
    }

    // This is a one-liner answer that uses STL function nth_element
    // which is a partial sorting algo that ensures the nth element is the same 
    // as if nums were fully sorted
    int findKthLargestNthElem(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
        return nums[k - 1];
    }

    // This is a one-liner answer that uses STL function partial_sort
    // which is a partial sorting algo that ensures the first k elements are sorted
    int findKthLargestParSort(vector<int>& nums, int k) {
        partial_sort(nums.begin(), nums.begin() + k, nums.end(), greater<int>());
        return nums[k - 1];
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> nums;
    int ans;

    nums = {3,2,1,5,6,4};
    ans = S->findKthLargest(nums, 2);
    cout << "Answer is " << ans << endl;

    ans = S->findKthLargestNthElem(nums, 2);
    cout << "Answer is " << ans << endl;

    ans = S->findKthLargestParSort(nums, 2);
    cout << "Answer is " << ans << endl;

    nums = {3,2,3,1,2,4,5,5,6};
    ans = S->findKthLargest(nums, 4);
    cout << "Answer is " << ans << endl;

    ans = S->findKthLargestNthElem(nums, 4);
    cout << "Answer is " << ans << endl;

    ans = S->findKthLargestParSort(nums, 4);
    cout << "Answer is " << ans << endl;
}

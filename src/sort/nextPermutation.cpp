#include <iostream>
#include <vector>
#include <stack>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/next-permutation/
Difficulty: Medium
Topics: Array, Sorting, Two Pointers
*/
class Solution {
public:
    // This is almost the same as the sort variant
    // But we can abuse the monotonically decreasing property of the subarray
    // and simply reverse it instead of sorting
    // resulting in a better time complexity
    void nextPermutation(vector<int>& nums) {
        stack<int> S;
        int sortOffset = 0;
        for (auto i=nums.size()-1; i>0; i--) {
            if (nums[i] > nums[i-1]) {
                // After swapping, we should sort from i to end
                sortOffset = i;

                int tmp = nums[i];
                int swapIndex = i;
                // Stack contains: nums[i+1], nums[i+2] ...
                while (!S.empty() && S.top() > nums[i-1]) {
                    tmp = S.top();
                    S.pop();
                    swapIndex++;
                }

                // perform the swap
                nums[swapIndex] = nums[i-1];
                nums[i-1] = tmp;
                break;
            } else {
                S.push(nums[i]);
            }
        }
        reverse(nums.begin()+sortOffset, nums.end());
    }

    // Given one permutation of nums, need to find the next lexicographically bigger permutation
    // Thus, the idea is to iterate from the back of the vector
    // and look for the first occurence (from back) of an "inversion", i.e. v[i] > v[i-1]
    // Imagine if nums is 4,3,2,1
    // Then nums is the largest permutation as no "inversion" exists
    // Then simply sort nums and done
    //
    // Assume inversion was found at some i
    // Then we should find the right number to swap with
    // Which is the smallest number at some index j, j>i which is bigger than nums[i]
    // Because we have done the check from back of nums, we know that nums[i+1:] must be 
    // monotonically decreasing
    // Thus simply traverse until k, where nums[k] <= nums[i] 
    // Then swap nums[i] with nums[k-1], then sort nums[i+1:]
    // This ensures the resulting array is lexicographically bigger than nums by the smallest possible margin
    void nextPermutationSort(vector<int>& nums) {
        stack<int> S;
        int sortOffset = 0;
        for (auto i=nums.size()-1; i>0; i--) {
            if (nums[i] > nums[i-1]) {
                // After swapping, we should sort from i to end
                sortOffset = i;

                int tmp = nums[i];
                int swapIndex = i;
                // Stack contains: nums[i+1], nums[i+2] ...
                while (!S.empty() && S.top() > nums[i-1]) {
                    tmp = S.top();
                    S.pop();
                    swapIndex++;
                }

                // perform the swap
                nums[swapIndex] = nums[i-1];
                nums[i-1] = tmp;
                break;
            } else {
                S.push(nums[i]);
            }
        }
        sort(nums.begin()+sortOffset, nums.end());
    }
};

int main() {
    vector<int> nums = {1,3,2};
    Solution *S = new Solution();
    S->nextPermutation(nums);
    printVec(nums);

    nums = {1,4,3,2};
    S->nextPermutation(nums);
    printVec(nums);

    nums = {4,3,2,1};
    S->nextPermutation(nums);
    printVec(nums);

    nums = {2,1,4,3};
    S->nextPermutation(nums);
    printVec(nums);
}

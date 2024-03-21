#include <vector>
#include <algorithm>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/rotate-array/
Difficulty: Medium
Topics: array, two pointers, math
*/
class Solution {
public:
    void rotate1(vector<int>& nums, int k) {
        int sz = nums.size();
        k = k%sz;
        vector<int> v2(nums.begin()+sz-k, nums.end());
        v2.insert(v2.end(), nums.begin(), nums.begin()+sz-k);
        nums = v2;
    }

    void rotate(vector<int>& nums, int k) {
        int pivot = nums.size() - k%nums.size();
        nums.insert(nums.end(), nums.begin(), nums.begin()+pivot);
        nums.erase(nums.begin(), nums.begin()+pivot);
    }

    // A clever solution using 3 reverse calls
    void rotateReverse(vector<int>& nums, int k) {
	k%=nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }

    // Concise solution abusing rotate std function
    void rotateShort(vector<int>& v, int k) {
	std::rotate(v.rbegin(), v.rbegin() + k%v.size(), v.rend());
    }

    void rotateShort2(vector<int>& v, int k) {
	std::rotate(v.begin(), v.begin() + v.size() - k%v.size(), v.end());
    }

};

int main() {
    Solution *S = new Solution();
    vector<int> v = {1,2,3,4,5,6,7};
    S->rotate(v, 3);
    printVec(v);

    v = {1,2,3,4,5,6,7};
    S->rotate1(v, 3);
    printVec(v);

    v = {1,2,3,4,5,6,7};
    S->rotateReverse(v, 3);
    printVec(v);

    v = {1,2,3,4,5,6,7};
    S->rotateShort(v, 3);
    printVec(v);

    v = {1,2,3,4,5,6,7};
    S->rotateShort2(v, 3);
    printVec(v);
}

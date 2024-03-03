#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/find-the-duplicate-number/description/
Difficulty: Medium
Topics: array, two pointers, binary search, bit manipulation
*/
class Solution {
public:
    // https://keithschwarz.com/interesting/code/?dir=find-duplicate
    // Mind-blowing explanation of why the tortoise and hare algorithm works here
    // Key point is to see that the input follows a "rho-shaped" cycle (like a sperm lol)
    // The fast pointer should catch the slow pointer at some point in the cycle
    // and it should have travelled a multiple of len(cycle) steps
    //
    // This means the slow pointer also travel a multiple of len(cycle) steps
    // So if advance the pointer finder c steps, where c is length of the rho's tail
    // and also the slow pointer c steps, then slow pointer would have taken c + m*len(cycle) steps
    // so slow pointer also stops at start of cycle
    int findDuplicate(vector<int>& nums) {
        int slow = nums.size()-1;
        int fast = slow;

        // let fast lap slow
        while (true) {
            slow = nums[slow] - 1;
            fast = nums[nums[fast] - 1] - 1;
            if (slow == fast) break;
        }

        // let pointer finder find slow
        int finder = nums.size()-1;
        while (finder != slow) {
            finder = nums[finder] - 1;
            slow = nums[slow] - 1;
        }

        return finder + 1;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v1 = {1,3,4,2,2};
    auto ans = S->findDuplicate(v1);
    cout << ans << endl;

    v1 = {3,1,3,4,2};
    ans = S->findDuplicate(v1);
    cout << ans << endl;
}

#include <iostream>
#include <queue>

using namespace std;

/*
Link: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips
Difficulty: Hard
Topics: array,bit manipulation,queue,sliding window,prefix sum
*/
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        queue<bool> Q;
        bool flipped = false;
        int totalFlips = 0;

        // It's straightforward to see why this works
        // But how to understand that it gives the optimal solution?
        for (auto i=0; i<nums.size(); i++) {
            // Process the Q first
            if (Q.size() == k) {
                flipped ^= Q.front();
                Q.pop();
            }

            if (flipped == nums[i]) {
                if (i+k > nums.size()) return -1;
                Q.push(true);
                flipped ^= true;
                totalFlips++;
            } else {
                Q.push(false);
                flipped ^= false;
            }
        }
        return totalFlips;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}

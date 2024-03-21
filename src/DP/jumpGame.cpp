#include <iostream>
using namespace std;

/*
Link: https://leetcode.com/problems/jump-game/
Difficulty: Medium
Topics: Array, DP, Greedy
*/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> DP(nums.size(), false);
        DP[DP.size()-1] = true;
        for (int i=nums.size()-2; i>=0; i--) {
            auto jumps = nums[i];
            for (auto j=1; j<=jumps; j++) {
                auto jumpIndex = i+j;
                if (jumpIndex >= nums.size()) break;
                if (DP[jumpIndex]) {
                    DP[i] = true;
                    break;
                }
            }
        }
        return DP[0];
    }

    // O(n) solution where we just keep track of one variable "minjump"
    // at some index i
    // is like the minimum jumping distance required to clear to the end
    // if can clear at index i, then minjump resets to 0
    // because subsequent j, just need jump to index i then is success
    bool canJumpGreedy(vector<int>& nums) {
        int i, minjump = 0;
        for(i = nums.size()-2; i >= 0; i--){
            minjump++;
            if(nums[i] >= minjump) minjump = 0;
        }

        if(minjump == 0) return true;
        else return false;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> l = {2,3,1,1,4};
    auto ans = S->canJump(l);
    cout << "answer is " << ans << endl;

    l = {3,2,1,0,4};
    ans = S->canJump(l);
    cout << "answer is " << ans << endl;
};

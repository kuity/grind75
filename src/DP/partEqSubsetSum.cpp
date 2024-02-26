#include <iostream>
#include <numeric>
#include <set>
using namespace std;

class Solution {
private:
    set<int> sumsPossible;
    vector<vector<bool>> DP;
    vector<bool> DP2;

public:
    // Possible to do an iterative bottom up soln with optimization
    bool canPartition(vector<int>& nums) {
        int target = 0;
        for (auto n: nums) { target += n; }
        if (target%2 != 0) { return false; }
        target /= 2;
        cout << "The target sum is " << target << endl;

        sumsPossible = {0};
        for (auto n: nums) {
            set<int> newSet;
            for (auto s: sumsPossible) {
                auto newS = s+n;
                // cout << "found sum " << newS << endl;

                // As long as there's one hit, can just end
                if (newS == target) {
                    return true;
                }

                if (newS <= target) {
                    newSet.insert(newS);
                }
            }
            sumsPossible.insert(newSet.begin(), newSet.end());
        }

        return false;
    }


    bool canPartitionDPHelper(vector<int>& nums, int target, int index=0) {
        cout << "target is " << target << ", index is " << index << endl;
        if (target == 0) return true;
        if (index >= nums.size() || target < 0) return false;
        if (DP[index][target] == true) return DP[index][target];
        DP[index][target] = (canPartitionDPHelper(nums, target-nums[index], index+1) 
            || canPartitionDPHelper(nums, target, index+1));
        return DP[index][target];
    }

    // Regular DP
    // We just want to find if there is a subset that sums to target in the current vector
    // This is true iff there is a subset that sums to target in the vector excluding element at index
    // OR : sums to (target-elem) in the vector excluding element at index
    // This shit fails the time check in l337code lmao
    bool canPartitionDP(vector<int>& nums) {
        int target = accumulate(nums.begin(), nums.end(), 0);
        if (target & 1) { return false; }
        vector<vector<bool>> dp(nums.size(), vector<bool>(target, false));
        DP = dp;
        target /= 2;
        return canPartitionDPHelper(nums, target);
    }

    // This DP solution is a bit like the first solution where the objective is to mark the possible sums
    // However, it's done using simple vector
    // Will loop over the nums vector from first num
    // The idea is to subtract current number from all numbers starting from target sum until the num
    // and check if the result is a valid sum
    // This will maximize the previous calculated results
    bool canPartitionDPBot(vector<int>& nums) {
        int target = accumulate(nums.begin(), nums.end(), 0);
        if (target & 1) { return false; }
        target /= 2;
        vector<bool> dp(target, false);
        dp[0] = true;
        for (auto n: nums) {
            for (auto s=target; s>=n; s--) {
                if (dp[s - n]) {
                    dp[s] = true;
                }
            }
        }

        return dp[target];
    }

    // This bitmask optimization 
    // is like a combination of approach 1 and the tabulation DP approach
    // in Tabulation approach, there is some inefficiency because we try all possibility between (num, target)
    // in approach 1, we are efficient but the set operation itself is slow
    // by representing possible sums as a bitmask and bitshifting, is an ingenious way
    // to add num to all prior sums, without using a loop
    bool canPartitionDPBM(vector<int>& nums) {
        int target = accumulate(nums.begin(), nums.end(), 0);
        if (target & 1) { return false; }
        target /= 2;
        bitset<20001> dp(1);

        for (auto n: nums) {
            dp = dp | dp << n;
        }

        return dp[target];
    }

};

int main() {
    Solution *S = new Solution();

    vector<int> V = {1,5,11,5};
    auto ans = S->canPartitionDPBM(V);
    cout << "Answer is " << ans << endl;
}

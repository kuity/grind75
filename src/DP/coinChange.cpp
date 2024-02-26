#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    /*
     * Efficient DP with an array (vector)
     * Here the critical part is figuring out the relationship between S[i] and S[j], where j>i
     * Here for S[j], we can check each S[j-c], where c in C, and get the minimum value
     * This works because each "optimal" combination of coins consists of a single coin from the bag, and a previous "optimal" combination of coins
     * finally, we just check S[n] for value
     */
    int coinChange(vector<int>& coins, int amount) {
        int INTMAX = numeric_limits<int>::max()-1;
        vector<int> tracker(++amount, INTMAX);
        tracker[0] = 0;
        for(int i=1; i<amount; i++) {
            for(auto c: coins) {
                int prev_i = i - c;
                if (prev_i < 0) {
                    continue;
                }
                tracker[i] = min(tracker[i], tracker[prev_i]+1);
            }
        }
        int val = tracker[--amount];
        if (val == INTMAX) {
            return -1;
        } else {
            return val;
        }
    }

    /* 
     * Less efficient DP using a queue and hashmap
    */
    int coinChangeSlow(vector<int>& coins, int amount) {
        unordered_map<int, int> leastmap;
        queue<pair<long, int>> coinQ;
        coinQ.push({0,0});
        leastmap[0] = 0;

        while(!coinQ.empty()) {
            pair<long, int> S = coinQ.front();
            int nextN = S.second + 1;
            coinQ.pop();
            for (auto c: coins) {
                long nextSum = S.first + c;
                if (nextSum > amount) {
                    continue;
                }

                if (leastmap.find(nextSum) != leastmap.end() && leastmap[nextSum] <= nextN) {
                    continue;
                } else {
                    leastmap[nextSum] = nextN;
                    coinQ.push({nextSum, nextN});
                }
            }
        }
        
        if (leastmap.find(amount) != leastmap.end()) {
            return leastmap[amount];
        } else {
            return -1;
        }
    }
};

int main() {
    vector<int> coins;
    int ans;
    Solution *S = new Solution();
    coins = {1,2,5};
    ans = S->coinChange(coins, 11);
    printVec(coins);
    cout << "ans is " << ans << endl;
    coins = {2};
    ans = S->coinChange(coins, 3);
    printVec(coins);
    cout << "ans is " << ans << endl;
    coins = {1};
    ans = S->coinChange(coins, 0);
    printVec(coins);
    cout << "ans is " << ans << endl;
    coins = {1,2147483647};
    ans = S->coinChange(coins, 2);
    printVec(coins);
    cout << "ans is " << ans << endl;
}

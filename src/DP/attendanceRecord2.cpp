#include <iostream>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/student-attendance-record-ii
Difficulty: Hard
Topics: DP
*/
class Solution {
public:
    long mod_exp(long exp, long mod) {
        long result = 1;
        long base = 2;
        while (exp > 0) {
            if (exp % 2 == 1) { // If exp is odd, multiply base with the result
                result = (result * base) % mod;
            }
            exp = exp >> 1;     // exp = exp / 2
            base = (base * base) % mod;  // base = base^2 % mod
        }
        return result;
    }

    // Intuitive DP solution breakdown
    // Disregard A first
    // If only P and L, the possibilities can be partitioned into 3 patterns
    // xxxP, xxxPL, xxxPLL (xxxPLLL is not possible, because cannot have 3 Late in a row)
    // Set up the DP to track the above 3 pattern for each length of string
    // answer = DP[n][0] + DP[n][1] + DP[n][2]
    // 
    // For A, consider 2 possible cases
    // case 1: no A. Then possibilies = answer
    // case 2: 1 A. Then possibilies = sum(possibilies) for each position of A, ranging from 0 to n-1
    // given some position i, then possibilities = (DP[i][0] + DP[i][1] + DP[i][2]) * (DP[n-i-1][0] + DP[n-i-1][1] + DP[n-i-1][2])
    // We just add case 1 and case 2 to get the final answer
    int checkRecord(int n) {
        int mod = 1e9+7;
        int dp[n+1][3];
        dp[0][0] = 1;
        dp[0][1] = 0;
        dp[0][2] = 0;
        dp[1][0] = 1;
        dp[1][1] = 1;
        dp[1][2] = 0;
        for(int i=2;i<=n;i++) {
            dp[i][0] = (0LL+dp[i-1][0]+dp[i-1][1]+dp[i-1][2])%mod;
            dp[i][1] = (0LL+dp[i-1][0])%mod;
            dp[i][2] = (0LL+dp[i-2][0])%mod;
        }

        long long ans = 0LL+dp[n][0]+dp[n][1]+dp[n][2];
        for(int i=0;i<n;i++) {
            int l = (0LL+dp[i][0]+dp[i][1]+dp[i][2])%mod;
            int r = (0LL+dp[n-1-i][0]+dp[n-1-i][1]+dp[n-1-i][2])%mod;
            ans = (ans+l*1LL*r)%mod;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    // for (auto i=9980; i<10122; i++) {
    //     ans = S->checkRecord(i);
    //     cout << "ans for " << i << " is " << ans << endl;
    // }
    for (auto i=1; i<30; i++) {
        ans = S->checkRecord(i);
        cout << "checkRecord: ans for " << i << " is " << ans << endl;
    }
    // ans = S->checkRecord(3);
    // cout << "ans for 3 is " << ans << endl;
    // ans = S->checkRecord(4);
    // cout << "ans for 4 is " << ans << endl;
    // ans = S->checkRecord(10101);
    // cout << "ans for 10101 is " << ans << endl;
}

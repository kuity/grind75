#include <iostream>

using namespace std;

class Solution {
private:
public:
    // This is just a reverse calculation because the movement
    // is highly constrained
    // (at each point, can only move down or right)
    // Thus, possible paths P(i,j) is simply P(i+1,j) + P(i,j+1)
    int uniquePaths(int m, int n) {
        int table[m][n];
        for (auto i=0; i<m; i++) table[i][n-1] = 1;
        for (auto i=0; i<n; i++) table[m-1][i] = 1;
        for (auto i=m-2; i>=0; i--)
            for (auto j=n-2; j>=0; j--)
                table[i][j] = table[i][j+1] + table[i+1][j];
        return table[0][0];
    }
};

int main() {
    int m = 3;
    int n = 7;
    Solution *S = new Solution();
    auto ans = S->uniquePaths(m, n);
    cout << "answer is " << ans << endl;
};

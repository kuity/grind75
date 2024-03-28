#include <algorithm>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/maximal-square/
Difficulty: Medium
Topics: Array, DP, Matrix
*/
class Solution {
public:
    // Idea: we can keep "shrinking" the matrix by scanning 2x2 subsections of it
    int maximalSquareSlow(vector<vector<char>>& matrix) {
        int sidelen = 0;
        for (auto v: matrix) 
            for (auto c: v) 
                if (c == '1') sidelen=1;
        if (sidelen == 0) return 0;

        while (true) {
            int sum = 0;
            vector<vector<char>> newM;
            // cout << "sidelen is " << sidelen << endl;
            for (auto i=0; i<matrix.size()-1; i++) {
                vector<char> newRow;
                for (auto j=0; j<matrix[0].size()-1; j++) {
                    if (matrix[i][j]=='1' && matrix[i][j+1]=='1'
                        && matrix[i+1][j]=='1' && matrix[i+1][j+1]=='1') {
                        newRow.push_back('1');
                        sum++;
                    } else newRow.push_back('0');
                }
                newM.push_back(newRow);
            }
            matrix = newM;
            // cout << "sum is " << sum << endl;
            if (sum==0) break;
            sidelen++;
        }
        return sidelen * sidelen;
    }

    // DP solution which is quite genius
    // base case: DP[0][0] = M[0][0] == '1' ? 1 : 0
    // recursive case: DP[i][j] = M[i][j] == '1' ? min(DP[i-1][j-1], DP[i][j-1], DP[i-1][j]) + 1 : 0
    // basically we need to check the cumulative value of the 3 neighbors
    int maximalSquare(vector<vector<char>>& matrix) {
        int nrows = matrix.size();
        int ncols = matrix[0].size();
        vector<vector<int>> DP(nrows, vector<int>(ncols, 0));

        int maxSquare = 0;
        for (auto i=0; i<nrows; i++) {
            for (auto j=0; j<ncols; j++) {
                if (matrix[i][j] == '0' || !i || !j) {
                    DP[i][j] = matrix[i][j] - '0';
                } else {
                    DP[i][j] = min(DP[i-1][j-1], min(DP[i][j-1], DP[i-1][j])) + 1;
                } 

                if (DP[i][j] > maxSquare) maxSquare = DP[i][j];
                // cout << "i is " << i << " j is " << j << endl;
                // cout << "DP value is " << DP[i][j] << endl;
            }
        }
        return maxSquare*maxSquare;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<vector<char>> M;

    M = {{'1','0','1','0','0'},
         {'1','0','1','1','1'},
         {'1','1','1','1','1'},
         {'1','0','0','1','0'}};
    ans = S->maximalSquare(M);
    cout << "ans is " << ans << endl;

    M = {{'0','1'},
         {'1','0'}};
    ans = S->maximalSquare(M);
    cout << "ans is " << ans << endl;
}

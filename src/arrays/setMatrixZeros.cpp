#include <vector>
#include <unordered_set>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/set-matrix-zeroes/
Difficulty: Medium
Topics: array, hash table, matrix
*/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_set<int> S;
        for (int i=0; i<matrix.size(); i++)
            for (int j=0; j<matrix[0].size(); j++)
                if (matrix[i][j] == 0) {
                    S.insert(i+1);
                    S.insert(-j-1);
                }

        for (auto k: S) 
            if (k > 0) for (auto i=0; i<matrix[0].size(); i++) matrix[k-1][i] = 0;
            else for (auto i=0; i<matrix.size(); i++) matrix[i][-(k+1)] = 0;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> M;
    M = {{1,1,1},{1,0,1},{1,1,1}};
    printVecVec(M);
    S->setZeroes(M);
    printVecVec(M);
}

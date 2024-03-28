#include <vector>
#include <algorithm>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/rotate-image/description/
Difficulty: Medium
Topics: array, matrix, math
*/
class Solution {
public:
    // Rotation is transpose + swap columns
    void rotate(vector<vector<int>>& matrix) {
        int row = matrix.size();
        for(int i=0;i<row; i++)
            for(int j=0; j<=i;j++)
                swap(matrix[i][j], matrix[j][i]);

        for(int i=0;i<row;i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> M;
    M = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};

    printVecVec(M);
    S->rotate(M);
    printVecVec(M);
}

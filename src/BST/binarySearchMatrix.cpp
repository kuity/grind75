#include <iostream>
#include <vector>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/search-a-2d-matrix
Difficulty: Medium
Topics: array, binary search, matrix
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int low = 0;
        int high = matrix.size()-1;
        int mid;
        while (high >= low) {
            mid = high-low / 2;
            if (matrix[mid][0] > target) high = mid-1;
            else if (matrix[mid][0] == target) return true;
            else low = mid+1;
        }
        auto rowIndex =  max(0, high);
        // cout << "rowIndex is " << rowIndex << endl;
        auto trow = matrix[rowIndex];
        auto found = lower_bound(trow.begin(), trow.end(), target);
        return !(found == trow.end()) && *found == target;
    }

    // This is an ingenious soln from leetcode which visualizes the matrix as a bst
    bool searchMatrixBST(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(),
            cols = matrix[0].size(),
            row = 0, col = cols - 1;
			
        while (row < rows && col > -1) {
            int cur = matrix[row][col];
            if (cur == target) return true;
            if (target > cur) row++;
            else col--;
        }
        
        return false;
    }
};

int main() {
    vector<vector<int>> M = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    Solution *S = new Solution();
    bool ans;
    ans = S->searchMatrix(M, 3);
    printVecVec(M);
    cout << "3 can be found: " << ans << endl << endl;

    M = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    ans = S->searchMatrix(M, 13);
    printVecVec(M);
    cout << "13 can be found: " << ans << endl << endl;
}

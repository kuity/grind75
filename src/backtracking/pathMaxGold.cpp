#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/path-with-maximum-gold/
Difficulty: Medium
Topics: dfs,array,backtracking,matrix
*/
class Solution {
public:
    int rows;
    int cols;
    int dfs(int i, int j, vector<vector<int>>& grid) {
        if(grid[i][j]==0) return 0;
        auto tmp = grid[i][j];
        int maxGold = tmp;
        grid[i][j] = 0;
        if(i>0) maxGold=max(maxGold,tmp+dfs(i-1,j,grid));
        if(j>0) maxGold=max(maxGold,tmp+dfs(i,j-1,grid));
        if(i<rows-1) maxGold=max(maxGold,tmp+dfs(i+1,j,grid));
        if(j<cols-1) maxGold=max(maxGold,tmp+dfs(i,j+1,grid));
        grid[i][j] = tmp;
        return maxGold;
    }

    int getMaximumGold(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

        int maxGold = 0;
        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                if (grid[i][j] == 0) continue;
                auto pathGold = dfs(i, j, grid);
                if (pathGold > maxGold) maxGold = pathGold;
            }
        }

        return maxGold;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<vector<int>> grid = {{0,6,0},{5,8,7},{0,9,0}};
    ans = S->getMaximumGold(grid);
    cout << "ans is " << ans;
}

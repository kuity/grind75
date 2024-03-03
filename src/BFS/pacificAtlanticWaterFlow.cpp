#include <iostream>
#include <queue>
#include "../../lib/util.h"
using namespace std;

/*
Link: https://leetcode.com/problems/pacific-atlantic-water-flow/
Difficulty: Medium
Topics: Array, DFS, BFS, Matrix
*/
class Solution {
    vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}}; 
    int rows;
    int cols;

public:
    void checkFlow(vector<vector<int>> &ocean, vector<vector<int>> &heights, 
                   queue<pair<int, int>> &Q) 
    {
        while (!Q.empty()) {
            auto coords = Q.front();
            Q.pop();
            auto row = coords.first;
            auto col = coords.second;
            auto h = heights[row][col];
            for (auto d: dirs) {
                auto nrow = row + d.first;
                auto ncol = col + d.second;
                if (nrow < 0 || nrow >= rows || ncol < 0 || ncol >= cols || 
                    heights[nrow][ncol] < h || ocean[nrow][ncol] == 1) continue;
                ocean[nrow][ncol] = 1;
                Q.push({nrow, ncol});
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        rows = heights.size();
        cols = heights[0].size();

        vector<vector<int>> pacific(rows, vector<int>(cols, 0));
        queue<pair<int, int>> Q;
        for (auto i=0; i<cols; i++) {Q.push({0, i}); pacific[0][i] = 1;}
        for (auto j=1; j<rows; j++) {Q.push({j, 0}); pacific[j][0] = 1;}
        checkFlow(pacific, heights, Q);

        vector<vector<int>> atlantic(rows, vector<int>(cols, 0));
        queue<pair<int, int>> R;
        for (auto i=0; i<cols; i++) {R.push({rows-1, i}); atlantic[rows-1][i] = 1;}
        for (auto j=0; j<rows-1; j++) {R.push({j, cols-1}); atlantic[j][cols-1] = 1;}
        checkFlow(atlantic, heights, R);

        vector<vector<int>> ans;
        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                if (pacific[i][j] == 1 && atlantic[i][j] == 1) ans.push_back({i, j});
            }
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> V;
    V = {{1,2,2,3,5},
         {3,2,3,4,4},
         {2,4,5,3,1},
         {6,7,1,4,5},
         {5,1,1,2,4}};
    auto ans = S->pacificAtlantic(V);
    printVecVec(ans);
}

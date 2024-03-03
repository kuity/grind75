#include <iostream>
#include <queue>
using namespace std;

/*
Link: https://leetcode.com/problems/shortest-path-to-get-food/
Difficulty: Medium
Topics: Array, BFS, Matrix
*/
class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> Q;
        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                if (grid[i][j] == '*') {Q.push({i, j}); break;}
            }
        }

        int cost = 0;
        while (!Q.empty()) {
            int sz = Q.size();
            for (int i=0; i<sz; i++) {
                auto row = Q.front().first;
                auto col = Q.front().second;
                Q.pop();
                vector<pair<int, int>> nbs = {{row-1, col}, {row+1, col}, {row, col-1}, {row, col+1}};
                for (auto nb: nbs) {
                    auto nbrow = nb.first;
                    auto nbcol = nb.second;
                    if (nbrow < 0 || nbrow >= rows || nbcol < 0 || nbcol >= cols || grid[nbrow][nbcol] == 'X') continue;
                    if (grid[nbrow][nbcol] == '#') return cost+1;
                    if (grid[nbrow][nbcol] == 'O') {
                        grid[nbrow][nbcol] = 'X';
                        Q.push({nbrow, nbcol});
                    }
                }
            }
            cost++;
        }
        return -1;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<char>> V;
    V = {{'X','X','X','X','X','X','X','X'},
         {'X','*','O','X','O','#','O','X'},
         {'X','O','O','X','O','O','X','X'},
         {'X','O','O','O','O','#','O','X'},
         {'X','X','X','X','X','X','X','X'}};
    auto ans = S->getFood(V);
    cout << "Answer is " << ans << endl;

    V = {{'X','X','X','X','X'},
        {'X','*','X','O','X'},
        {'X','O','X','#','X'},
        {'X','X','X','X','X'}};
    ans = S->getFood(V);
    cout << "Answer is " << ans << endl;
}

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/number-of-islands/
Difficulty: Medium
Topics: array, dfs, bfs, union find, matrix
*/
class Solution {
public:
    // DFS traversal
    void traversal(int i, int j, int m, int n, vector<vector<char>>& grid) {
	stack<pair<int, int>> tStack;
	tStack.push({i, j});
	while(!tStack.empty()) {
	    auto [x, y] = tStack.top();
	    grid[x][y] = '0';
	    if (y+1 < n && grid[x][y+1] == '1') {
		tStack.push({x, y+1});
	    } else if (x+1 < m && grid[x+1][y] == '1') {
		tStack.push({x+1, y});
	    } else if (x > 0 && grid[x-1][y] == '1') {
		tStack.push({x-1, y});
	    } else if (y > 0 && grid[x][y-1] == '1') {
		tStack.push({x, y-1});
	    } else {
		tStack.pop();
	    }
	}
    }

    int numIslands(vector<vector<char>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	int num = 0;

	// queue<pair<int, int>> toVisit;
	for (int i=0; i<m; i++) {
	    for (int j=0; j<n; j++) {
		// cout << "i is " << i << ",j is " << j << endl;
		if (grid[i][j] == '1') {
		    num++;
		    traversal(i, j, m, n, grid);
		}
	    }
	}
	return num;
    }
};

int main() {
    vector<vector<char>> grid = {
      {'1','1','0','0','0'},
      {'1','1','0','0','0'},
      {'0','0','1','0','0'},
      {'0','0','0','1','1'}
    };
    Solution *S = new Solution();
    int ans;
    ans = S->numIslands(grid);
    cout << "ans is " << ans << endl;

    grid =  {
      {'1','1','1','1','0'},
      {'1','1','0','1','0'},
      {'1','1','0','0','0'},
      {'0','0','0','0','0'}
    };
    ans = S->numIslands(grid);
    cout << "ans is " << ans << endl;

    grid = {
	{'1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','0','1','1'},
	{'0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0'},
	{'1','0','1','1','1','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','0','1','1','1','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1'},
	{'0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1'},
	{'1','0','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','0'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}};
    ans = S->numIslands(grid);
    cout << "ans is " << ans << endl;
}

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
class UnionFind {
    int rows, cols;
    vector<int> Parent;
public:
    int count;
    int getIndex(int m, int n) {
        return m*cols + n;
    }

    UnionFind(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        count = 0;
        Parent = vector<int>(rows*cols);
        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                if (grid[i][j] == '0') continue;
                auto index = getIndex(i, j);
                Parent[index] = index;
                count++;
            }
        }
    }

    int find(int c) {
        if (Parent[c] == c) return c;
        Parent[c] = find(Parent[c]);
        return Parent[c];
    }

    void ufunion(int a, int b) {
        auto parentA = find(a);
        auto parentB = find(b);
        if (parentA != parentB) {
            Parent[parentA] = parentB;
            count--;
        }
    }
};

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

    int numIslandsUF(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        UnionFind *UF = new UnionFind(grid);
        
        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                if (grid[i][j] == '0') continue;
                auto indexA = UF->getIndex(i, j);
                if (i+1<rows && grid[i+1][j] == '1') {
                    auto indexB = UF->getIndex(i+1, j);
                    UF->ufunion(indexA, indexB);
                }
                if (i-1>=0 && grid[i-1][j] == '1') {
                    auto indexB = UF->getIndex(i-1, j);
                    UF->ufunion(indexA, indexB);
                }
                if (j+1<cols && grid[i][j+1] == '1') {
                    auto indexB = UF->getIndex(i, j+1);
                    UF->ufunion(indexA, indexB);
                }
                if (j-1>=0 && grid[i][j-1] == '1') {
                    auto indexB = UF->getIndex(i, j-1);
                    UF->ufunion(indexA, indexB);
                }
            }
        }
        return UF->count;
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

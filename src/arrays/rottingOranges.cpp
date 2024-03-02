#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/*
Link: https://leetcode.com/problems/rotting-oranges/description/
Difficulty: Medium
Topics: array, bfs, matrix
*/
class Solution {
private:
	// Define a custom hash function for pairs of integers
	struct pair_hash {
		inline std::size_t operator()(const std::pair<int, int>& p) const {
			// Compute individual hash values for first and second
			// and combine them using XOR and bit shifting:
			
			auto hash1 = std::hash<int>{}(p.first);
			auto hash2 = std::hash<int>{}(p.second);
			
			return hash1 ^ (hash2 << 1);
		}
	};
	unordered_map<pair<int, int>, bool, pair_hash> HM;
	queue<pair<int, int>> Q;

public:
    // This is a BFS traversal that returns the number of time-steps
	// Use a hashmap to track which positions have been visited
	// If visited, don't visit anymore
    int traversal(int m, int n, vector<vector<int>>& grid) {
		int mins = 0;
		bool stateChanged = false;
		while(!Q.empty()) {
			auto checks = Q.size();
			for (auto t=0; t<checks; t++) {
				auto [x, y] = Q.front();
				if (y+1 < n && grid[x][y+1] == 1 && HM[{x, y+1}] != true) {
					HM[{x, y+1}] = true;
					Q.push({x, y+1});
					grid[x][y+1] = 2;
					stateChanged = true;
				} 
				if (x+1 < m && grid[x+1][y] == 1 && HM[{x+1, y}] != true) {
					HM[{x+1, y}] = true;
					Q.push({x+1, y});
					grid[x+1][y] = 2;
					stateChanged = true;
				} 
				if (x > 0 && grid[x-1][y] == 1 && HM[{x-1, y}] != true) {
					HM[{x-1, y}] = true;
					Q.push({x-1, y});
					grid[x-1][y] = 2;
					stateChanged = true;
				} 
				if (y > 0 && grid[x][y-1] == 1 && HM[{x, y-1}] != true) {
					HM[{x, y-1}] = true;
					Q.push({x, y-1});
					grid[x][y-1] = 2;
					stateChanged = true;
				} 
				Q.pop();
			}

			// printVecVec(grid);
			if (stateChanged) {
				mins++;
				stateChanged = false;
			}
		}

		return mins;
    }

    int orangesRotting(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();

		// Initialize the Q
		for (auto i=0; i<m; i++) {
			for (auto j=0; j<n; j++) {
				if (grid[i][j]==2) {
					Q.push({i, j});
					HM[{i, j}] = true;
				}
			}
		}

		int mins = traversal(m, n, grid);

		// Check if any orange left
		for (auto i=0; i<m; i++) {
			for (auto j=0; j<n; j++) {
				if (grid[i][j]==1) {
					return -1;
				}
			}
		}

		return mins;
    }
};

int main() {
    vector<vector<int>> grid = {
      {2, 1, 1},
      {1, 1, 0},
      {0, 1, 1}
    };

    Solution *S = new Solution();
    int ans;
    ans = S->orangesRotting(grid);
    cout << "ans is " << ans << endl;

    grid =  {
      {2, 1, 1},
      {0, 1, 1},
      {1, 0, 1}
    };
    ans = S->orangesRotting(grid);
    cout << "ans is " << ans << endl;

    grid = {
		{0, 2}
	};
    ans = S->orangesRotting(grid);
    cout << "ans is " << ans << endl;
}

#include <vector>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/flood-fill/description/
Difficulty: Easy
Topics: array, dfs, bfs, matrix
*/
class Solution {
public:
    void helper(vector<vector<int>> & image, int color, int rows, int cols, 
		int row, int col, int scolor) 
    {
	if (row < 0 || col < 0 || row >= rows || col >= cols) return;
        auto c = image[row][col];
        if (c == scolor && c != color) {
            image[row][col] = color;
            helper(image, color, rows, cols, row-1, col, scolor);
            helper(image, color, rows, cols, row+1, col, scolor);
            helper(image, color, rows, cols, row, col-1, scolor);
            helper(image, color, rows, cols, row, col+1, scolor);
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        helper(image, color, image.size(), image[0].size(), sr, sc, image[sr][sc]);
        return image;
    }
};

int main() {
    vector<vector<int>> image = {{1,1,1},{1,1,0},{1,0,1}};
    Solution *S = new Solution();
    S->floodFill(image, 1, 1, 2);
    for (auto v: image) printVec(v);

    vector<vector<int>> image2 = {{0,0,0},{0,0,0}};
    S->floodFill(image2, 0, 0, 0);
    for (auto v: image2) printVec(v);
}

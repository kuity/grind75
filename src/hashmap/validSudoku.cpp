#include <unordered_map>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/valid-sudoku/
Difficulty: Medium
Topics: Hashtable, Array, Matrix
*/
class Solution {
    unordered_map<int, vector<bool>> M;

public:
    bool checkIndex(int index, char val) {
	int num = val - '0';
	bool ret = M[index][num];
	// cout << "Check index " << index << " and num " << num << endl;
	M[index][num] = false;
	return ret;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
	for (int i=0; i<3*9; i++) M[i] = vector<bool>(10, true);
	for (int i=0; i<9; i++) {
	    for (int j=0; j<9; j++) {
		auto val = board[i][j];
		if (val == '.') continue;
		int rowIndex = i;
		int colIndex = 9+j;
		int gridIndex = 2*9 + (i/3)*3 + (j/3);
		if ((checkIndex(rowIndex, val) &&
		    checkIndex(colIndex, val) &&
		    checkIndex(gridIndex, val)) != true) return false;
	    }
	}
	return true;
    }
};

int main() {
    vector<vector<char>> board = 
	{{'5','3','.','.','7','.','.','.','.'}
	,{'6','.','.','1','9','5','.','.','.'}
	,{'.','9','8','.','.','.','.','6','.'}
	,{'8','.','.','.','6','.','.','.','3'}
	,{'4','.','.','8','.','3','.','.','1'}
	,{'7','.','.','.','2','.','.','.','6'}
	,{'.','6','.','.','.','.','2','8','.'}
	,{'.','.','.','4','1','9','.','.','5'}
	,{'.','.','.','.','8','.','.','7','9'}};

    Solution *S = new Solution();
    auto ans = S->isValidSudoku(board);
    cout << "Testcase 1: " << ans << endl;

    board = 
	{{'8','3','.','.','7','.','.','.','.'}
	,{'6','.','.','1','9','5','.','.','.'}
	,{'.','9','8','.','.','.','.','6','.'}
	,{'8','.','.','.','6','.','.','.','3'}
	,{'4','.','.','8','.','3','.','.','1'}
	,{'7','.','.','.','2','.','.','.','6'}
	,{'.','6','.','.','.','.','2','8','.'}
	,{'.','.','.','4','1','9','.','.','5'}
	,{'.','.','.','.','8','.','.','7','9'}};
    ans = S->isValidSudoku(board);
    cout << "Testcase 2: " << ans << endl;
}

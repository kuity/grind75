#include <iostream>
#include <unordered_map>
using namespace std;

/*
Link: https://leetcode.com/problems/word-search/description/
Difficulty: Medium
Topics: array, string, backtracking, matrix
*/
class Solution {
private:
    vector<vector<char>> B;
    int nRows;
    int nCols;

public:
    bool helper(pair<int, int> position, string word) {
        if (word.size() == 0) return true;
        auto row = position.first;
        auto col = position.second;
        if (row < 0 || row >= nRows || col < 0 || col >= nCols) return false;
        auto c = B[row][col];
        if (c != word[0]) return false;
        B[row][col] = '$';
        vector<pair<int, int>> neighbors = {{row-1, col}, {row+1, col}, {row, col-1}, {row, col+1}};
        for (auto n: neighbors) {
            if (helper(n, word.substr(1))) return true;
        }
        B[row][col] = c;
        return false;
    }

    // Try a brute-force solution
    // with sanity check (enough characters in the board itself)
    //
    // From online: instead of using stupid set, we just modify the board itself la
    bool exist(vector<vector<char>>& board, string word) {
        B = board;
        nRows = board.size();
        nCols = board[0].size();

        unordered_map<char, int> freqs;
        for (auto v: board) for (auto c: v) freqs[c]++;
        for (auto c: word) {
            freqs[c]--;
            if (freqs[c] < 0) return false;
        }

        for (int i=0; i<nRows; i++) {
            for (int j=0; j<nCols; j++) {
                cout << "Search position (" << i << "," << j << ")" << endl;
                if (helper({i, j}, word)) return true;
            }
        }
        return false;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<char>> V = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    auto ans = S->exist(V, "ABCCED");
    cout << "Answer is " << ans << endl;
    ans = S->exist(V, "SEE");
    cout << "Answer is " << ans << endl;
    ans = S->exist(V, "ABCB");
    cout << "Answer is " << ans << endl;
    V = {{'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'}};
    ans = S->exist(V, "AAAAAAAAAAAAAAB");
    V = {{'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','A'},
        {'A','A','A','A','A','B'},
        {'A','A','A','A','B','A'}};
    ans = S->exist(V, "AAAAAAAAAAAAABB");
    cout << "Answer is " << ans << endl;
}

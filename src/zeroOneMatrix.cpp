#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<int> v) {
    for (int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void printVecVec(vector<vector<int>> v) {
    for (auto x: v) {
        printVec(x);
    }
    std::cout << std::endl;
}


// Bottom up idea
// SCORE is 0
// First look for the zeros and add them to STACK 
// go through STACK and update M to SCORE if M = -1 or SCORE < M
// add neighbors to STACK as long as they have no score
// It ends when STACK.size() == 0
// increment SCORE and go back to step 1
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
	int rows = mat.size();
	int cols = mat[0].size();
	vector<vector<int>> score(rows, vector<int>(cols, -1));
	vector<pair<int, int>> stack;
	int currentScore = 0;

	for (int i=0; i<rows; i++) {
	    for (int j=0; j<cols; j++) {
		if (mat[i][j] == 0) {
		    stack.push_back(make_pair(i, j));
		}
	    }
	}

	while(stack.size() > 0) {
	    vector<pair<int, int>> neighbors;
	    for (auto p : stack) {
		int j = p.first;
		int k = p.second;
		if (score[j][k] == -1 || currentScore < score[j][k]) {
		    score[j][k] = currentScore;
		    if (j > 0 && score[j-1][k] == -1) {
			neighbors.push_back(make_pair(j-1, k));
		    }
		    if (j < rows-1 && score[j+1][k] == -1) {
			neighbors.push_back(make_pair(j+1, k));
		    }
		    if (k > 0 && score[j][k-1] == -1) {
			neighbors.push_back(make_pair(j, k-1));
		    }
		    if (k < cols-1 && score[j][k+1] == -1) {
			neighbors.push_back(make_pair(j, k+1));
		    }
		}
	    }
	    stack = neighbors;
	    currentScore++;
	}

	return score;
    }
};


int main() {
    Solution *S = new Solution();
    // vector<vector<int>> v1 = {{0,0,0},{0,1,0},{0,0,0}};
    // vector<vector<int>> a1 = S->updateMatrix(v1);

    vector<vector<int>> v1 = {{0,0,0},{0,1,0},{1,1,1}};
    vector<vector<int>> a1 = S->updateMatrix(v1);
    printVecVec(v1);
    printVecVec(a1);
}

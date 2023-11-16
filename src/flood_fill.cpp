#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

class Solution {
private:
    vector<vector<int>>* imagep = nullptr;
    int height = 0;
    int width = 0;
    set<tuple<int, int>> visit = {};

public:
    void printImage(vector<vector<int>>& i) {
	for (const auto& inner : i) {
	    for(int num: inner) {
		cout << num << ",";
	    }
	    cout << endl;
	}
    }

    void printSelfImage() {
	printImage(*imagep);
    }

    void setImage(vector<vector<int>>& newImage) {
        imagep = &newImage;
	height = newImage.size();
	width = newImage[0].size();
    }

    void helper(int cr, int cc, int pr, int pc, int color) {
	// cout << "visiting:" << cr << "," << cc << endl;
	if (visit.find(make_tuple(cr, cc)) != visit.end()) {
	    return;
	}
	if (cr<0 || cr>=height) {
	    return;
	}
	if (cc<0 || cc>=width) {
	    return;
	}
	if ((*imagep)[cr][cc] != (*imagep)[pr][pc]) {
	    return;
	}

	visit.insert(make_tuple(cr, cc));
	helper(cr-1, cc, cr, cc, color);
	helper(cr, cc-1, cr, cc, color);
	helper(cr+1, cc, cr, cc, color);
	helper(cr, cc+1, cr, cc, color);
	(*imagep)[cr][cc] = color;
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color){
	setImage(image);
	helper(sr, sc, sr, sc, color);
	(*imagep)[sr][sc] = color;
	return *imagep;
    }
};

int main() {
    vector<vector<int>> image = {{1,1,1},{1,1,0},{1,0,1}};
    Solution *S = new Solution();
    S->printImage(image);
    S->floodFill(image, 1, 1, 2);
    S->printSelfImage();

    vector<vector<int>> image2 = {{0,0,0},{0,0,0}};
    S->printImage(image2);
    S->floodFill(image2, 0, 0, 0);
    S->printSelfImage();

}

#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    // Brute force: nested for loop can account for all containers
    // Optimization: with skips (based on current max area width and height)
    int maxArea2(vector<int>& height) {
        auto mA = 0;
        auto mADist = 1;
        auto mAHeight = 0;

        for (int left=height.size()-2; left>=0; left--) {
            auto deezHeight = height[left];
            if (deezHeight == 0) continue; // this can't produce any meaningful area
            auto toSkip = mA / deezHeight;
            auto rightIndex = left+toSkip; // not physically possible for indices before this to have larger area
            for (int right=rightIndex; right<height.size(); right++) {
                cout << "left is " << left << ", right is " << right << endl;
                auto h = min(deezHeight, height[right]);
                auto dist = right-left;
                if (h*dist > mA) {
                    cout << "new max is " << h*dist << endl;
                    mA = h*dist;
                    mADist = dist;
                    mAHeight = h;
                }
            }
        }

        return mA;
    }

    // Logical math solution, just start 2 pointers at head and tail of array and
    // attempt to increment / decrement
    //
    // Why it works? 
    // head and tail means we start with widest possible container
    // a larger container MUST be narrower, thus it MUST be taller
    // the height is set to EITHER the tail or head index 
    // At each step, no point moving the taller end, as that won't change the area
    // Literally, we can only move the shorter end, means there is only 1 possible path and the search can't miss anything
    //
    // Thus, IF there exists 2 ends with a bigger area, we WILL find it
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        auto h = 0;
        auto area = (right-left)*h;
        while (left < right) {
            h = min(height[left], height[right]);
            auto newArea = (right-left)*h;
            if (newArea > area) area = newArea;
            // cout << "left is " << left << ", right is " << right << endl;
            while (height[left] <= h && left<right) left++;
            while (height[right] <= h && left<right) right--;
        }

        return area;
    }
};

int main() {
    vector<int> heights = {1,8,6,2,5,4,8,3,7};
    Solution *S = new Solution();
    auto ans = S->maxArea(heights);
    cout << "answer is " << ans << endl;
};

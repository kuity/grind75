#include <iostream>
#include <vector>
#include <map>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/meeting-rooms-ii/description/
Difficulty: Medium
Topics: array,two pointers,greedy,sorting,heap,prefix sum
*/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> M;
        for (auto v: intervals) {
            M[v[0]]++;
            M[v[1]]--;
        }

        int max = 0;
        int current = 0;
        for (auto p: M) {
            current += p.second;
            if (current > max) max = current;
        }
        
        return max;
    }
};

int main() {
    Solution *S = new Solution();
    vector<vector<int>> v1 = {{0,30},{5,10},{15,20}};
    int a1 = S->minMeetingRooms(v1);
    printVecVec(v1);
    cout << "answer is " << a1 << endl;
}

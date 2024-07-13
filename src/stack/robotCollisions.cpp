#include <iostream>
#include <numeric>
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/robot-collisions
Difficulty: Hard
Topics: array, stack, sorting, simulation
*/
class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        vector<int> indices(positions.size());
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&positions](int a, int b) {
            return positions[a] < positions[b];
        });

        stack<int> rights;
        for (int i: indices) {
            if (directions[i] == 'R') rights.push(i);
            else {
                auto index2 = i;
                while (!rights.empty() && healths[index2] > 0) {
                    auto index1 = rights.top();
                    if (healths[index2] > healths[index1]) {
                        healths[index1] = 0;
                        healths[index2]--;
                        rights.pop();
                    } else if (healths[index2] == healths[index1]) {
                        healths[index1] = 0;
                        healths[index2] = 0;
                        rights.pop();
                    } else {
                        healths[index1]--;
                        healths[index2] = 0;
                    }
                }
            }
        }

        vector<int> ans;
        for (auto i: healths) 
            if (i > 0) ans.push_back(i);
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}

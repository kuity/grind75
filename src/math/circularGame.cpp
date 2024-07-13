#include <iostream>
#include <numeric>

using namespace std;

/*
Link: https://leetcode.com/problems/find-the-winner-of-the-circular-game
Difficulty: Medium
Topics: array, math, queue, recursion, simulation
*/
class Solution {
public:
    int findTheWinner(int n, int k) {
        vector<int> V(n);
        iota(V.begin(), V.end(), 1);
        int index = 0;
        while(V.size() > 1) {
            index = (index + k - 1) % V.size();
            // cout << "removing " << V[index] << " at index " << index << endl;
            V.erase(V.begin()+index);
        }
        return V[0];
    }
};

int main() {
    Solution *S = new Solution();
    int n, k;
    int ans;
    n = 5;
    k = 2;
    ans = S->findTheWinner(n, k);
    cout << "ans is " << ans << endl;
}

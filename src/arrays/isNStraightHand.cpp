#include <iostream>
#include <map>

using namespace std;

/*
Link: https://leetcode.com/problems/hand-of-straights/
Difficulty: Medium
Topics: array, hashtable, greedy, sorting
*/
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;
        map<int, int> M;
        for (auto i: hand) M[i]++;
        while(!M.empty()) {
            auto it = M.begin();
            auto k = it->first;
            auto v = it->second;
            M.erase(k);
            for (int i=1; i<groupSize; i++) {
                auto index = k+i;
                if (M.find(index) == M.end()) return false;
                M[index]-=v;
                if (M[index] < 0) return false;
                if (M[index] == 0) M.erase(index);
            }
        }

        return true;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> hand = {1,2,3,6,2,3,4,7,8};
    bool ans = S->isNStraightHand(hand, 3);
    cout << "ans is " << ans << endl;
    hand = {1,2,3,4,5};
    ans = S->isNStraightHand(hand, 3);
    cout << "ans is " << ans << endl;
}

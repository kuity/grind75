#include <algorithm>
#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/magnetic-force-between-two-balls
Difficulty: Medium
Topics: array, binary search, sorting
*/
class Solution {
public:
    bool canFitBalls(int m, int d, vector<int>& D) {
        auto it = D.begin();
        auto tgt = m;
        int dist = 0;
        while (it != D.end() && tgt >= 0) {
            dist += *it++;
            if (dist >= d) {
                tgt--;
                dist = 0;
            }
        }
        return tgt <= 0;
    }


    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        vector<int> D;
        for (auto i=1; i<position.size(); i++) {
            D.push_back(position[i] - position[i-1]);
        }

        int lo = *min_element(D.begin(), D.end());
        int hi = *position.rbegin() - *position.begin();
        while (hi >= lo) {
            int mid = (hi + lo) / 2;
            cout << "hi: " << hi << " lo: " << lo << " mid: " << mid << endl;
            auto canFit = canFitBalls(m-1, mid, D);
            if (canFit) lo = mid+1;
            else hi = mid-1;
        }
        return hi;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> baskets;
    int m;
    int ans;
    m = 3;
    baskets = {1,2,3,4,7};
    cout << "baskets: ";
    printVec(baskets);
    ans = S->maxDistance(baskets, m);
    cout << "ans for m = " << m << " is " << ans << endl;

    m = 2;
    baskets = {5,4,3,2,1,1000000000};
    cout << "baskets: ";
    printVec(baskets);
    ans = S->maxDistance(baskets, m);
    cout << "ans for m = " << m << " is " << ans << endl;

    m = 4;
    baskets = {79,74,57,22};
    cout << "baskets: ";
    printVec(baskets);
    ans = S->maxDistance(baskets, m);
    cout << "ans for m = " << m << " is " << ans << endl;
}

#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/count-number-of-nice-subarrays
Difficulty: Medium
Topics: array,hashtable,math,sliding window
*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        vector<int> P;
        int ans = 0;
        for (auto i=0; i<nums.size(); i++) {
            if (nums[i] % 2 == 1) P.push_back(i);
        }
        if (P.size() < k) return ans;
        P.insert(P.begin(), -1);
        P.push_back(nums.size());

        vector<int> D;
        for (auto i=0; i<P.size()-1; i++) {
            D.push_back(P[i+1]-P[i]);
        }
        // printVec(P);
        // printVec(D);

        int head = 0;
        int tail = k;
        while(tail < D.size()) {
            ans += D[head] * D[tail];
            // cout << "head is " << head << " tail is " << tail << " ans is " << ans << endl;
            head++;
            tail++;
        }
        return ans;
    }

    // Same solution but slightly optimized
    int numberOfSubarraysOpt(vector<int>& nums, int k) {
        vector<int> D;
        int ans = 0;
        int index = -1;
        int numOdd = 0;
        for (auto i=0; i<nums.size(); i++) {
            if (nums[i] % 2 == 1) {
                D.push_back(i-index);
                index = i;
                numOdd++;
            }
        }
        if (numOdd < k) return ans;
        D.push_back(nums.size()-index);
        int head = 0;
        int tail = k;
        while(tail < D.size()) {
            ans += D[head] * D[tail];
            head++;
            tail++;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> v;
    int k;
    v = {1,1,2,1,1};
    k = 3;
    ans = S->numberOfSubarrays(v, k);
    cout << "ans is " << ans << endl;

    v = {2,2,2,1,2,2,1,2,2,2};
    k = 2;
    ans = S->numberOfSubarrays(v, k);
    cout << "ans is " << ans << endl;

    v = {2,4,6};
    k = 1;
    ans = S->numberOfSubarrays(v, k);
    cout << "ans is " << ans << endl;
}


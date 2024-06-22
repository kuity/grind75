#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/relative-sort-array
Difficulty: Easy
Topics: array, hashtable, sort, counting sort
*/
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int arrlen = 1001;
        int M[arrlen];
        memset(M, 0, sizeof(M));
        for (auto i: arr1) M[i]++;
        int index = 0;
        for (auto x: arr2) {
            auto val = M[x];
            fill(arr1.begin()+index, arr1.begin()+index+val, x);
            M[x] = 0;
            index+=val;
        }

        for (auto i=0; i<arrlen; i++) {
            int val = M[i];
            if (val == 0) continue;
            fill(arr1.begin()+index, arr1.begin()+index+val, i);
            index+=val;
        }
        return arr1;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> v = {2,3,1,3,2,4,6,7,9,2,19};
    printVec(v);
    vector<int> a = {2,1,4,3,9,6};
    auto ans = S->relativeSortArray(v, a);
    printVec(ans);

    v = {28,6,22,8,44,17};
    printVec(v);
    a = {22,28,8,6};
     ans = S->relativeSortArray(v, a);
    printVec(ans);

}

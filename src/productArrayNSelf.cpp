#include <iostream>
#include <vector>
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = nums.size();
        vector<int> ans(N, 1);
        int backward = 1;
        int forward = 1;
        for (auto i=N-1; i>0; i--) {
            backward*=nums[i];
            ans[i-1]=backward;
        }
        for (auto i=0; i<N-1; i++) {
            forward*=nums[i];
            ans[i+1]*=forward;
        }
        return ans;
    }
};

int main() {
    vector<int> v;
    vector<int> ans;
    Solution *S = new Solution();
    v = {1,2,3,4};
    ans = S->productExceptSelf(v);
    printVec(v);
    printVec(ans);

    v = {-1,1,0,-3,3};
    ans = S->productExceptSelf(v);
    printVec(v);
    printVec(ans);
}

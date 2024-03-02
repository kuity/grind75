#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<int> v) {
    for (int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

/*
Link: https://leetcode.com/problems/maximum-subarray/
Difficulty: Medium
Topics: array, divide and conquer, dp
*/
class Solution {
public:
    /* 
     * The first idea is using 3 loops and a lot of precalculation
     * For every index i in the array, we maintain the MINIMUM sum seen so far from index 0 to index i-1 (Bmin)
     * AND the MINIMUM sum seen so far from index i+1 to end (Amin)
     * By default Bmin == 0, in the case no elements are discarded from the subarray
     * If however Bmin < 0, then it means at some index x <= i-1, the sum is < 0, so we can discard elements 0 to x, to increase the subarray sum
     * The same logic applies for Amin
     *
     * The second method is just an optimization of the first idea to use 2 loops instead
     *
     * The third method is a DP solution tracking a global maximum
     * Given an array A, define subproblem S(i) to mean the maximum subarray of A[0:i] which must contain A[i].
     * Then the max subarray of A is simply the maximum S(i) over each posible value of i.
     * By this definition, it follows that S(i) = [ S(i-1) > 0 ? S(i-1) : 0 ] + A[i]
     *
    */
    int maxSubArrayDp(vector<int>& nums) {
	long globalMax = nums[0];
	vector<long> dp(nums.size());

	dp[0] = nums[0];
	for (int i=1; i<nums.size(); i++) {
	    dp[i] = (dp[i-1] > 0 ? dp[i-1] : 0) + nums[i];
	    if (dp[i] > globalMax) {
		globalMax = dp[i];
	    }
	}
	return globalMax;
    }

    int maxSubArray(vector<int>& nums) {
	vector<int> sumsFromStart = {};
	vector<int> sumsToEnd = {};
	long finalSum = 0;

	// First populate sumsFromStart
	for (int x: nums) {
	    sumsFromStart.push_back(finalSum);
	    finalSum += x;
	}
	//printVec(sumsFromStart);

	// Next populate sumsToEnd
	long sumsToEndCounter = finalSum;
	for (int x: nums) {
	    sumsToEndCounter -= x;
	    sumsToEnd.push_back(sumsToEndCounter);
	}
	//printVec(sumsToEnd);

	// Now, get the "minimum sumFromStart(exclusive) seen so far at every index, starting from 0"
	long minSumFromStart = sumsFromStart[0];
	for (int i=0; i<sumsFromStart.size(); i++) {
	    if (sumsFromStart[i] < minSumFromStart) {
		minSumFromStart = sumsFromStart[i];
	    } else {
		sumsFromStart[i] = minSumFromStart;
	    }
	}
	//printVec(sumsFromStart);

	// Now, get the "minimum sumToEnd(exclusive) seen so far at every index, starting from 0"
	long minSumToEnd = sumsToEnd[sumsToEnd.size()-1];
	for (int i=(sumsToEnd.size()-1); i>=0; i--) {
	    if (sumsToEnd[i] < minSumToEnd) {
		minSumToEnd = sumsToEnd[i];
	    } else {
		sumsToEnd[i] = minSumToEnd;
	    }
	}
	//printVec(sumsToEnd);

	// At each position, sum minimum sumFromStart and minimum sumToEnd and find the minimum
	long minimumPossible = 0;
	for (auto i=0; i<sumsFromStart.size(); i++) {
            long combined = sumsFromStart[i] + sumsToEnd[i];
	    if (combined < minimumPossible) {
		minimumPossible = combined;
	    }
	}

	return finalSum - minimumPossible;
    }

    int maxSubArrayOpt(vector<int>& nums) {
	vector<int> calculation(nums.size());
	long totalSum;
	long minCounter = 0;
	long counter = 0;

	// Populate calculation from the back
	for (int i=nums.size()-1; i>=0; i--) {
	    calculation[i] = minCounter;
	    counter += nums[i];
	    if (counter < minCounter) {
		minCounter = counter;
	    }
	}
	totalSum = counter;

	long minFromFront = 0;
	long overallMin = 0;
	counter = 0;
	for (int i=0; i<nums.size(); i++) {
	    long tmp = minFromFront + calculation[i];
	    if (tmp < overallMin) {
		overallMin = tmp;
	    }
	    counter += nums[i];
	    if (counter < minFromFront) {
		minFromFront = counter;
	    }
	}

	return totalSum - overallMin;
    }
};

int main() {
    vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    Solution *S = new Solution();
    int ans;
    ans = S->maxSubArrayDp(v);
    cout << "ans is " << ans << endl;

    vector<int> v2 = {5,4,-1,7,8};
    ans = S->maxSubArrayDp(v2);
    cout << "ans is " << ans << endl;
    vector<int> v3 = {-1};
    ans = S->maxSubArrayDp(v3);
    cout << "ans is " << ans << endl;

    vector<int> v4 = {-2,-1};
    ans = S->maxSubArrayDp(v4);
    cout << "ans is " << ans << endl;
}

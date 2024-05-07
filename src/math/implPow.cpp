#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/powx-n/
Difficulty: Medium
Topics: math, recursion
*/
class Solution {
    unordered_map<int, double> cache;
public:
    double myPow(double x, long n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        if (n < 0) return 1 / myPow(x, -n);

        // let's add an optimization for when n is super big
        long halfn = n/2;
        long halfn2 = n-halfn;
        double pow1 = myPow(x, halfn);
        cache[halfn] = pow1;
        if (halfn == halfn2) return pow1 * pow1;
        double pow2 = myPow(x, halfn2);
        cache[halfn2] = pow2;
        return pow1 * pow2;
    }

    // Here is a very nice solution with bitshifting that doesn't need recursion
    double myPowShift(double x, int n) {
        if(n < 0) x = 1/x;
        long num = labs(n);
        double pow = 1;
        
        while(num) { // equivalent to while(num != 0)
            if(num & 1) { // equivalent to if((num & 1) != 0)
                pow *= x;
            }
            x *= x;
            num >>= 1;
        }
        return pow;
    }
};

int main() {
    Solution *S = new Solution();
    double ans;
    ans = S->myPow(2.0, 10);
    cout << "myPow(2.0, 10) is " << ans << endl;
    ans = S->myPow(2.1, 3);
    cout << "myPow(2.1, 3) is " << ans << endl;
    ans = S->myPow(2.0, -2);
    cout << "myPow(2.0, -2) is " << ans << endl;
}

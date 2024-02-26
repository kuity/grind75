#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool isBadVersion(int n) {
	if (n >= 2000) {
	    return true;
	} else {
	    return false;
	}
    }

public:
    int firstBadVersion(int n) {
	bool isBad;
	long lower = 0;
	long upper = n-1;
	long mid;
	while (upper>=0 && lower<n && upper>=lower) {
	    mid = (lower+upper)/2;
	    cout << "mid is now " << mid << endl;
	    if (isBadVersion(mid)) {
		upper = mid-1;
	    } else {
		lower = mid+1;
	    }
	}

	if (isBadVersion(mid)) {
	    return mid;
	} else {
	    return mid+1;
	}
    }
};

int main() {
    int n = 2001;
    Solution *S = new Solution();
    int ans = S->firstBadVersion(n);
    cout << "first bad version is " << ans << endl;
}

#include <iostream>

using namespace std;


class Solution {
public:
    bool isPalindrome(string s) {
	int last = s.size()-1;
	int first = 0;
	while (first < last) {
	    char firstchar = s.at(first);
	    char lastchar = s.at(last);
	    if (!(isalpha(firstchar) || isdigit(firstchar))) {
		first++;
	    } else if (!(isalpha(lastchar) || isdigit(lastchar))) {
		last--;
	    } else if (tolower(lastchar) != tolower(firstchar)) {
		return false;
	    } else {
		first++;
		last--;
	    }
	}
	return true;
    }
};

int main() {
    // vector<int> list1 = {7, 1, 5, 3 ,6, 4};
    string s1 = "A man, a plan, a canal: Panama";
    string s2 = "race a car";
    Solution *S = new Solution();
    bool a1 = S->isPalindrome(s1);
    cout << a1 << endl;
    bool a2 = S->isPalindrome(s2);
    cout << a2 << endl;
};

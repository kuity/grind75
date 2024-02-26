#include <cctype>
#include <iostream>
#include <limits>

using namespace std;

class Solution {
public:
    int myAtoi(string s) {
	string parsed = "";
	int sign = 1;
	int maxint_len = 10;
	int maxint = numeric_limits<int>::max();
	int minint = numeric_limits<int>::min();

	int index = 0;
	while (index < s.size()) {
	    if (isspace(s[index])) {
		index++;
	    } else {
		break;
	    }
	}

	if (s[index] == '-') {
	    sign = -1;
	    index++;
	} else if (s[index] == '+') {
	    index++;
	}

	// ignore leading zeros
	while (index < s.size()) {
	    if (s[index] == '0') {
		index++;
	    } else {
		break;
	    }
	}

	while (index < s.size()) {
	    auto c = s[index];
	    if (isdigit(c)) { parsed += c; index++; } else { break; }
	    if (parsed.size() > maxint_len) { break; }
	}

	if (parsed.size() == 0) {
	    return 0;
	}

	cout << "parsed is " << parsed << endl;
	long converted = stol(parsed) * sign;
	// cout << "converted is " << converted << endl;
	if (converted > maxint) {
	    return maxint;
	} else if (converted < minint) {
	    return minint;
	} else {
	    return converted;
	}
    }
};

int main() {
    string input = "   -42";
    Solution *S = new Solution();
    auto ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input = "4193 with word";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input = "20502013023020";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input = "-95092349349393";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input = "+95092349349393";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input = "words and 987";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
    input =    "  0000000000012345678";
    ans = S->myAtoi(input);
    cout << "ans is " << ans << endl;
}

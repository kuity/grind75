#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
Difficulty: Medium
Topics: array, math, stack
*/
class Solution {
public:
    pair<int, int> pop2 (stack<int> & S) {
        int op2 = S.top();
        S.pop();
        int op1 = S.top();
        S.pop();
        return {op1, op2};
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> S;
        int op1, op2;

        for (auto s: tokens) {
            if (s == "*") {
                tie(op1, op2) = pop2(S);
                S.push(op1 * op2);
            } else if (s == "/") {
                tie(op1, op2) = pop2(S);
                S.push(op1 / op2);
            } else if (s == "+") {
                tie(op1, op2) = pop2(S);
                S.push(op1 + op2);
            } else if (s == "-") {
                tie(op1, op2) = pop2(S);
                S.push(op1 - op2);
            } else {
                S.push(stoi(s));
            }
        }
        return S.top();
    }
};

int main() {
    vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    vector<string> tokens2 = {"2","1","+","3","*"};
    vector<string> tokens3 = {"4","13","5","/","+"};
    Solution *S = new Solution();
    int ans = S->evalRPN(tokens);
    int ans2 = S->evalRPN(tokens2);
    int ans3 = S->evalRPN(tokens3);
    cout << ans << endl;
    cout << ans2 << endl;
    cout << ans3 << endl;
}

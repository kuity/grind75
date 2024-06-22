#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone
Difficulty: Easy
Topics: array, greedy, sorting
*/
class Solution {
public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());
        int moves = 0;
        for (auto i=0; i<students.size(); i++) moves += abs(seats[i] - students[i]);
        return moves;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    vector<int> seats = {4,1,5,9};
    vector<int> students = {1,3,2,6};
    ans = S->minMovesToSeat(seats, students);
    cout << "ans is " << ans << endl;

    seats = {2,2,6,6};
    students = {1,3,2,6};
    ans = S->minMovesToSeat(seats, students);
    cout << "ans is " << ans << endl;
}

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
link: https://leetcode.com/problems/minimum-knight-moves/
difficulty: medium
topics: BFS
*/
class Solution {
    vector<pair<int, int>> moves = {
        {2, 1},
        {2, -1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {1, -2},
        {-1, -2}
    };

public:
    // Initially, I thought Dijkstra's algo
    // But then the cost is uniform because the cost always increments by one (move)
    // So it's actually a BFS
    // Instead of having to use a PQ, the FIFO Queue is good enough
    //
    // Optimization: Apparently, there's a way to greedily optimize by reducing x and y 
    // until both x and y are less than 4
    // This will drastically reduce the search space
    int minKnightMoves(int x, int y) {
        x = abs(x) + 1;
        y = abs(y) + 1;
        vector<vector<bool>> visited(x+3, vector<bool>(y+3, false));
        queue<pair<pair<int, int>, int>> Q;
        Q.push({{1, 1}, 0});

        auto it = 0;
        while (!Q.empty()) {
            auto nextPos = Q.front().first;
            auto cost = Q.front().second;
            Q.pop();
            auto nx = nextPos.first;
            auto ny = nextPos.second;
            if (visited[nx][ny]) continue;
            // cout << "iteration " << it << ": x is " << nx << ", y is " << ny << ", cost is " << cost << endl;
            visited[nx][ny] = true;
            if (nx == x && ny == y) return cost;

            for (auto m: moves) {
                auto nbX = nx + m.first;
                auto nbY = ny + m.second;
                // We don't want the position to "stray" too much
                if (nbX < 0 || nbX > x+2) continue;
                if (nbY < 0 || nbY > y+2) continue;
                if (visited[nbX][nbY]) continue;
                Q.push({{nbX, nbY}, cost+1});
            }
            ++it;
        }
        return 0;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    ans = S->minKnightMoves(2, 1);
    cout << "move to (2, 1) need " << ans << " moves" << endl;

    ans = S->minKnightMoves(5, 5);
    cout << "move to (5, 5) need " << ans << " moves" << endl;

    ans = S->minKnightMoves(2, 112);
    cout << "move to (2, 112) need " << ans << " moves" << endl;

    ans = S->minKnightMoves(25, -87);
    cout << "move to (25, -87) need " << ans << " moves" << endl;

    ans = S->minKnightMoves(0, 2);
    cout << "move to (0, 2) need " << ans << " moves" << endl;
}

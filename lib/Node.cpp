#include "Node.h"
#include <queue>
#include <vector>
#include <iostream>

void printAdjacency(Node * n) {
    queue<Node *> v;
    vector<bool> visited(101, false);

    if (n!=nullptr) {
        v.push(n);
        visited[n->val] = true;
    }

    while(!v.empty()) {
        Node * nxt = v.front();
        v.pop();
        if (nxt != nullptr) {
            cout << nxt->val << ": ";
            for (auto nb: nxt->neighbors) {
                cout << nb->val << ",";
                if (!visited[nb->val]) {
                    v.push(nb);
                    visited[nb->val] = true;
                }
            }
            cout << endl;
        }
    }
}

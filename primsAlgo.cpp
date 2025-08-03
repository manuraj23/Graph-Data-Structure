#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int, int> P; // weight, vertex

int main() {
    int V = 4;
    vector<vector<P>> graph(V);
    // Add edges
    graph[0].push_back({1, 1});
    graph[1].push_back({1, 0});
    graph[1].push_back({3, 2});
    graph[2].push_back({3, 1});
    graph[1].push_back({2, 3});
    graph[3].push_back({2, 1});
    graph[0].push_back({4, 2});
    graph[2].push_back({4, 0});
    graph[2].push_back({5, 3});
    graph[3].push_back({5, 2});

    vector<bool> inMST(V, false);
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, 0});
    int mstWeight = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        mstWeight += w;
        for (auto& [weight, v] : graph[u]) {
            if (!inMST[v]) pq.push({weight, v});
        }
    }

    cout << "MST weight = " << mstWeight << "\n";
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
};

int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 1}, {1, 3, 2}, {1, 2, 3},
        {0, 2, 4}, {2, 3, 5}
    };

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(V);
    int mstWeight = 0;
    vector<Edge> mst;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            mst.push_back(e);
        }
    }

    cout << "MST weight = " << mstWeight << "\nEdges:\n";
    for (auto& e : mst) {
        cout << e.u << " - " << e.v << " : " << e.w << "\n";
    }
}

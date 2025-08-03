#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18; // sufficiently large

// Runs Floyd-Warshall on weighted graph with n vertices (0..n-1).
// adj matrix should have weight or INF if no direct edge.
// Returns distance matrix and next matrix for path reconstruction.
pair<vector<vector<long long>>, vector<vector<int>>> floyd_warshall(vector<vector<long long>> dist) {
    int n = dist.size();
    vector<vector<int>> next(n, vector<int>(n, -1));

    // initialize next for direct edges
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] < INF) next[i][j] = j;
        }
        dist[i][i] = min(dist[i][i], 0LL);
        next[i][i] = i;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    return {dist, next};
}

// Reconstruct path from u to v. Returns empty vector if no path or negative cycle affects it.
vector<int> reconstruct_path(int u, int v, const vector<vector<int>> &next, const vector<vector<long long>> &dist) {
    if (next[u][v] == -1) return {}; // no path
    // check for negative cycle on the path: if dist[i][i] < 0 for any i reachable on path, it's ambiguous
    // (optional stronger detection could be added)
    vector<int> path = {u};
    while (u != v) {
        u = next[u][v];
        if (u == -1) return {}; // should not happen
        path.push_back(u);
        if ((int)path.size() > dist.size() + 5) break; // safeguard against loops
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // number of vertices (0-indexed)
    int m;
    cin >> m; // number of edges

    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // in case of multiple edges
    }

    auto [d, next] = floyd_warshall(dist);

    // Detect negative cycles: any d[i][i] < 0
    bool hasNegCycle = false;
    for (int i = 0; i < n; ++i) {
        if (d[i][i] < 0) {
            hasNegCycle = true;
            break;
        }
    }

    if (hasNegCycle) {
        cout << "Warning: graph contains a negative cycle.\n";
    }

    // Output distance matrix
    cout << "Distance matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] >= INF/2) cout << "INF ";
            else cout << d[i][j] << ' ';
        }
        cout << '\n';
    }

    // Example: reconstruct one path query
    int q;
    cin >> q; // number of path queries
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (next[u][v] == -1) {
            cout << "No path from " << u << " to " << v << "\n";
        } else {
            vector<int> path = reconstruct_path(u, v, next, d);
            cout << "Path from " << u << " to " << v << ": ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i + 1 < path.size()) cout << " -> ";
            }
            cout << "\n";
        }
    }

    return 0;
}

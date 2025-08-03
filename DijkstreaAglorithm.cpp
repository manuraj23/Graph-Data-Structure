#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = numeric_limits<ll>::max();

// Returns pair of (distances vector, parent vector)
pair<vector<ll>, vector<int>> dijkstra(int src, const vector<vector<pair<int, ll>>> &adj) {
    int n = adj.size();
    vector<ll> dist(n, INF);
    vector<int> parent(n, -1);
    dist[src] = 0;
    
    // min-heap of (distance, node)
    priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, src);
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // stale entry

        for (auto &[v, weight] : adj[u]) {
            if (dist[u] != INF && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    return {dist, parent};
}

// Reconstruct path from src to target using parent array.
// Returns empty vector if unreachable.
vector<int> reconstruct_path(int target, const vector<int> &parent) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    // Example input:
    // V = number of vertices (0-indexed assumed: vertices [0..V-1])
    // E = number of edges
    // Then E lines: u v w  (edge from u to v with weight w)
    // Then source vertex src.
    cin >> V >> E;
    vector<vector<pair<int, ll>>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // If undirected graph, add both directions:
        // adj[u].emplace_back(v, w);
        // adj[v].emplace_back(u, w);
        
        // Directed:
        adj[u].emplace_back(v, w);
    }

    int src;
    cin >> src;

    auto [dist, parent] = dijkstra(src, adj);

    // Output distances
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            cout << "Vertex " << i << " is unreachable from source " << src << "\n";
        } else {
            cout << "Distance to vertex " << i << " = " << dist[i] << "\n";
        }
    }

    // Example: print path to each node
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) continue;
        vector<int> path = reconstruct_path(i, parent);
        cout << "Path to " << i << ": ";
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j];
            if (j + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }

    return 0;
}

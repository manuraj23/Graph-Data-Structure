#include <iostream>
#include <vector>
#include <limits>
#include <string>
using namespace std;

struct Edge {
    string u, v;
    int w;
};

void bellmanFord(vector<Edge>& edges, vector<string>& vertices, string source) {
    // Initialize distances
    const int INF = numeric_limits<int>::max();
    unordered_map<string, int> dist;
    for (auto& v : vertices) dist[v] = INF;
    dist[source] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < vertices.size() - 1; i++) {
        for (auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            cout << "Graph contains a negative weight cycle\n";
            return;
        }
    }

    // Print results
    for (auto& v : vertices) {
        cout << v << ": " << (dist[v] == INF ? -1 : dist[v]) << "\n";
    }
}

int main() {
    vector<string> vertices = {"A", "B", "C", "D"};
    vector<Edge> edges = {
        {"A", "B", 4},
        {"A", "C", 2},
        {"B", "C", -1},
        {"C", "D", 2},
        {"D", "B", -2}
    };

    bellmanFord(edges, vertices, "A");
}

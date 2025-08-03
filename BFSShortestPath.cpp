#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

vector<string> bfsShortestPath(unordered_map<string, vector<string>>& graph,
                               const string& start, const string& target) {
    queue<string> q;
    set<string> visited;
    unordered_map<string, string> parent; // to reconstruct path

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        string node = q.front(); q.pop();
        if (node == target) {
            // reconstruct path
            vector<string> path;
            for (string at = target; !at.empty(); at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for (const string& neighbor : graph[node]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }
    return {}; // no path
}

int main() {
    unordered_map<string, vector<string>> graph;
    graph["A"] = {"B", "C"};
    graph["B"] = {"D"};
    graph["C"] = {"E"};
    graph["D"] = {"F"};
    graph["E"] = {"F"};
    graph["F"] = {};

    string start = "A", target = "F";
    vector<string> path = bfsShortestPath(graph, start, target);

    if (!path.empty()) {
        cout << "Shortest path: ";
        for (string node : path) cout << node << " ";
        cout << "\n";
    } else {
        cout << "No path found.\n";
    }
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

// Recursive DFS
void dfsRecursive(const string& node,
                  unordered_map<string, vector<string>>& graph,
                  set<string>& visited) {
    if (visited.count(node)) return;
    visited.insert(node);
    cout << node << " ";
    for (const string& neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
            dfsRecursive(neighbor, graph, visited);
        }
    }
}

int main() {
    // Build example graph:
    // A -> B, C
    // B -> D, E
    // C -> (none)
    // D -> (none)
    // E -> (none)
    unordered_map<string, vector<string>> graph;
    graph["A"] = {"B", "C"};
    graph["B"] = {"D", "E"};
    graph["C"] = {};
    graph["D"] = {};
    graph["E"] = {};

    cout << "Recursive DFS starting from A: ";
    set<string> visited;
    dfsRecursive("A", graph, visited);
    cout << "\n";

    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
using namespace std;

// Iterative DFS using explicit stack
void dfsIterative(const string& start,
                  unordered_map<string, vector<string>>& graph) {
    set<string> visited;
    stack<string> st;
    st.push(start);

    while (!st.empty()) {
        string node = st.top();
        st.pop();
        if (visited.count(node)) continue;
        visited.insert(node);
        cout << node << " ";
        // Push neighbors in reverse order to mimic recursive visitation order
        for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it) {
            if (!visited.count(*it)) {
                st.push(*it);
            }
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

    cout << "Iterative DFS starting from A: ";
    dfsIterative("A", graph);
    cout << "\n";

    return 0;
}

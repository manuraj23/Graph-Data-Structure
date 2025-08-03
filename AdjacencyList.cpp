#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V = 4;
    vector<int> adj[4];

    // Add edges
    adj[0].push_back(1); // A-B
    adj[1].push_back(0);
    adj[1].push_back(2); // B-C
    adj[2].push_back(1);
    adj[0].push_back(3); // A-D
    adj[3].push_back(0);
    adj[2].push_back(3); // C-D
    adj[3].push_back(2);

    // Print adjacency list
    for (int i = 0; i < V; i++) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

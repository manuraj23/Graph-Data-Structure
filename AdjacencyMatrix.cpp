#include <iostream>
using namespace std;

int main() {
    int V = 4;
    int graph[4][4] = {0};

    // Add edge A-B (0-1)
    graph[0][1] = 1;
    graph[1][0] = 1;

    // Add edge B-C (1-2)
    graph[1][2] = 1;
    graph[2][1] = 1;

    cout << "Adjacency Matrix:\n";
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<pair<int,int>> edges;

    // Add edges
    edges.push_back({0,1}); // A-B
    edges.push_back({1,2}); // B-C
    edges.push_back({2,3}); // C-D
    edges.push_back({3,0}); // D-A

    cout << "Edge List:\n";
    for (auto e : edges) {
        cout << e.first << " -- " << e.second << endl;
    }
}


#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void prim(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> mstSet(n, 0);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1, minKey = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!mstSet[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }

        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    prim(graph);

    return 0;
}

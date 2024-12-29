
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v, w;
};

void bellmanFord(int n, int m, vector<Edge>& edges, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Negative-weight cycle detected.\n";
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << ": " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int src;
    cin >> src;

    bellmanFord(n, m, edges, src);

    return 0;
}

#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void floyd(vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<int>> d = g;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] != INT_MAX && d[k][j] != INT_MAX) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (d[i][j] == INT_MAX ? "INF " : to_string(d[i][j]) + " ");
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> g(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    floyd(g);

    return 0;
}

void warshall(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<vector<int>> r = adj;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i][j] = r[i][j] || (r[i][k] && r[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    warshall(adj);

    return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#define INF INT_MAX / 2

class Dijkstra {
public:
    int n; // Number of nodes
    vector<int> dist, pred, vis; // Distance, predecessor, and visited status arrays
    int srcIdx, currNode; // Source index and current node
    vector<vector<int>> adjMat; // Cost matrix
    map<string, int> nodeToIdx; // Map nodes to indices
    map<int, string> idxToNode; // Map indices to node names

    void loadNetwork(const string& fname) {
        ifstream file(fname);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            string start, end;
            int weight;

            if (line.empty() || line[0] == '#') continue;

            getline(ss, start, ',');
            getline(ss, end, ',');
            ss >> weight;

            if (nodeToIdx.find(start) == nodeToIdx.end()) {
                nodeToIdx[start] = n;
                idxToNode[n] = start;
                n++;
                adjMat.resize(n);
                for (int j = 0; j < n; ++j) {
                    adjMat[j].resize(n, INF);
                }
            }
            if (nodeToIdx.find(end) == nodeToIdx.end()) {
                nodeToIdx[end] = n;
                idxToNode[n] = end;
                n++;
                adjMat.resize(n);
                for (int j = 0; j < n; ++j) {
                    adjMat[j].resize(n, INF);
                }
            }

            adjMat[nodeToIdx[start]][nodeToIdx[end]] = weight;
            adjMat[nodeToIdx[end]][nodeToIdx[start]] = weight;
        }

        file.close();
    }

    void init() {
        vis.resize(n, 0);

        cout << "Enter source node: ";
        string src;
        cin >> src;

        if (nodeToIdx.find(src) == nodeToIdx.end()) {
            cout << "Error: Source node not found." << endl;
            return;
        }

        srcIdx = nodeToIdx[src];
        vis[srcIdx] = 1;

        pred.resize(n);
        dist.resize(n, INF);
        dist[srcIdx] = 0;

        for (int i = 0; i < n; i++) {
            pred[i] = srcIdx;
        }

        currNode = srcIdx;
    }

    void calcSP() {
        int nearest = -1;

        for (int i = 0; i < n; i++) {
            if (!vis[i] && (nearest == -1 || dist[i] < dist[nearest])) {
                nearest = i;
            }
        }

        currNode = nearest;
        vis[currNode] = 1;

        for (int i = 0; i < n; i++) {
            if (!vis[i] && adjMat[currNode][i] != INF &&
                dist[currNode] + adjMat[currNode][i] < dist[i]) {
                dist[i] = dist[currNode] + adjMat[currNode][i];
                pred[i] = currNode;
            }
        }
    }

    void printSP(int destIdx) {
        vector<int> path;
        for (int curr = destIdx; curr != srcIdx; curr = pred[curr]) {
            path.push_back(curr);
        }
        path.push_back(srcIdx);

        for (int i = path.size() - 1; i > 0; i--) {
            cout << idxToNode[path[i]] << " -> ";
        }
        cout << idxToNode[path[0]] << "\tTotal cost: " << dist[destIdx] << endl;
    }

    void showReachable() {
        cout << "Reachable Nodes from " << idxToNode[srcIdx] << ":\n";
        for (int i = 0; i < n; i++) {
            if (dist[i] != INF) {
                cout << idxToNode[i] << " (Distance: " << dist[i] << ")\n";
            }
        }
    }
};

int main() {
    Dijkstra algo;
    algo.loadNetwork("city_map.txt");

    algo.init();
    for (int i = 0; i < algo.n - 1; i++) {
        algo.calcSP();
    }

    algo.showReachable();

    cout << "\nShortest Paths:\n";
    for (int i = 0; i < algo.n; i++) {
        if (i != algo.srcIdx) {
            cout << "To " << algo.idxToNode[i] << ": ";
            algo.printSP(i);
        }
    }

    return 0;
}

Here is the code with all the comments removed:

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#define INF INT_MAX / 2

class SmartEnergyManagement {
public:
    int totalNodes;
    vector<int> distances, predecessors, visited;
    int sourceIndex, currentNode;
    vector<vector<int>> adjacencyMatrix;
    map<string, int> nameToIndex;
    map<int, string> indexToName;

    void loadGraph(const string& fileName) {
        ifstream inputFile(fileName);
        string line;

        while (getline(inputFile, line)) {
            istringstream lineStream(line);
            string nodeStart, nodeEnd;
            int edgeWeight;

            if (line.empty() || line[0] == '#') continue;

            getline(lineStream, nodeStart, ',');
            getline(lineStream, nodeEnd, ',');
            lineStream >> edgeWeight;

            if (nameToIndex.find(nodeStart) == nameToIndex.end()) {
                nameToIndex[nodeStart] = totalNodes;
                indexToName[totalNodes] = nodeStart;
                totalNodes++;
                adjacencyMatrix.resize(totalNodes);
                for (int j = 0; j < totalNodes; ++j) {
                    adjacencyMatrix[j].resize(totalNodes, INF);
                }
            }
            if (nameToIndex.find(nodeEnd) == nameToIndex.end()) {
                nameToIndex[nodeEnd] = totalNodes;
                indexToName[totalNodes] = nodeEnd;
                totalNodes++;
                adjacencyMatrix.resize(totalNodes);
                for (int j = 0; j < totalNodes; ++j) {
                    adjacencyMatrix[j].resize(totalNodes, INF);
                }
            }

            adjacencyMatrix[nameToIndex[nodeStart]][nameToIndex[nodeEnd]] = edgeWeight;
            adjacencyMatrix[nameToIndex[nodeEnd]][nameToIndex[nodeStart]] = edgeWeight;
        }

        inputFile.close();
    }

    void initialize() {
        visited.resize(totalNodes, 0);

        cout << "Enter source energy node (e.g., power plant): ";
        string sourceName;
        cin >> sourceName;

        if (nameToIndex.find(sourceName) == nameToIndex.end()) {
            cout << "Error: Source node not found." << endl;
            return;
        }

        sourceIndex = nameToIndex[sourceName];
        visited[sourceIndex] = 1;

        predecessors.resize(totalNodes);
        distances.resize(totalNodes, INF);
        distances[sourceIndex] = 0;

        for (int i = 0; i < totalNodes; i++) {
            predecessors[i] = sourceIndex;
        }

        currentNode = sourceIndex;
    }

    void calculateShortestPaths() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        minHeap.push({0, sourceIndex});

        while (!minHeap.empty()) {
            int distanceToCurrent = minHeap.top().first;
            int current = minHeap.top().second;
            minHeap.pop();

            if (visited[current]) continue;
            visited[current] = 1;

            for (int neighbor = 0; neighbor < totalNodes; neighbor++) {
                if (!visited[neighbor] && adjacencyMatrix[current][neighbor] != INF &&
                    distanceToCurrent + adjacencyMatrix[current][neighbor] < distances[neighbor]) {

                    distances[neighbor] = distanceToCurrent + adjacencyMatrix[current][neighbor];
                    predecessors[neighbor] = current;
                    minHeap.push({distances[neighbor], neighbor});
                }
            }
        }
    }

    void printShortestPath(int destinationIndex) {
        vector<int> path;
        for (int current = destinationIndex; current != sourceIndex; current = predecessors[current]) {
            path.push_back(current);
        }
        path.push_back(sourceIndex);

        for (int i = path.size() - 1; i > 0; i--) {
            cout << indexToName[path[i]] << " -> ";
        }
        cout << indexToName[path[0]] << "\tTotal energy cost: " << distances[destinationIndex] << endl;
    }

    void showAllReachableNodes() {
        cout << "Reachable Energy Nodes from " << indexToName[sourceIndex] << ":\n";
        for (int i = 0; i < totalNodes; i++) {
            if (distances[i] != INF) {
                cout << indexToName[i] << " (Energy cost: " << distances[i] << ")\n";
            }
        }
    }
};

int main() {
    SmartEnergyManagement algorithm;
    algorithm.loadGraph("energy_network.txt");

    algorithm.initialize();
    algorithm.calculateShortestPaths();

    algorithm.showAllReachableNodes();

    cout << "\nShortest Energy Distribution Paths:\n";
    for (int i = 0; i < algorithm.totalNodes; i++) {
        if (i != algorithm.sourceIndex) {
            cout << "To " << algorithm.indexToName[i] << ": ";
            algorithm.printShortestPath(i);
        }
    }

    return 0;
}
```

In this version, all the comments have been removed to make the code cleaner. The functionality remains the same, with the program calculating and displaying the shortest energy distribution paths based on the Dijkstra algorithm.

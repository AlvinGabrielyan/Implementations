#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int destination, weight;
};

class Graph {
private:
    vector<vector<Edge>> adjList;
    int numNodes;

public:
    Graph(int n) {
        numNodes = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(numNodes, INT_MAX);
        dist[src] = 0;
        vector<bool> visited(numNodes, false);

        for (int i = 0; i < numNodes - 1; ++i) {
            int minDist = INT_MAX, u = -1;
            for (int j = 0; j < numNodes; ++j) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            visited[u] = true;

            for (const Edge& e : adjList[u]) {
                if (!visited[e.destination] && dist[u] + e.weight < dist[e.destination]) {
                    dist[e.destination] = dist[u] + e.weight;
                }
            }
        }

        return dist;
    }
};

int main() {
    int n = 7;
    Graph g(n);

    g.addEdge(0, 1, 5);
    g.addEdge(0, 3, 12);
    g.addEdge(0, 6, 25);
    g.addEdge(1, 0, 5);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 5);
    g.addEdge(2, 6, 10);
    g.addEdge(3, 0, 12);
    g.addEdge(3, 1, 8);
    g.addEdge(3, 2, 2);
    g.addEdge(4, 2, 4);
    g.addEdge(4, 6, 5);
    g.addEdge(5, 6, 5);

    vector<int> distances = g.dijkstra(0);

    cout << "The shortest path from A to G has length: " << distances[6] << endl;

    return 0;
}

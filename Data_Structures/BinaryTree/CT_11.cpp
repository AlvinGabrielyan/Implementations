#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Graph {
private:
    const int rows = 7;
    const int cols = 7;
    string matrix[7][7] = {
        { "0", "n1", "n2", "n3", "n4", "n5", "n6" },
        { "n1", "0", "10", "0", "0", "8", "5" },
        { "n2", "10", "0", "0", "20", "12", "0" },
        { "n3", "0", "0", "0", "4", "0", "0" },
        { "n4", "0", "20", "4", "0", "15", "0" },
        { "n5", "8", "12", "0", "15", "0", "7" },
        { "n6", "5", "0", "0", "0", "7", "0" }
    };

public:
    Graph() {}

    void printAdjList() {
        const int numNodes = 6;
        vector<char> nodeLabels = { 'A', 'B', 'C', 'D', 'E', 'F' };
        vector<list<int>> adjList(numNodes);

        adjList[0] = { 1, 2 };       // A -> B, C
        adjList[1] = { 0, 2, 3, 5 }; // B -> A, C, D, F
        adjList[2] = { 0, 1 };       // C -> A, B
        adjList[3] = { 1, 4, 5 };    // D -> B, E, F
        adjList[4] = { 3 };          // E -> D
        adjList[5] = { 1, 3 };       // F -> B, D

        cout << "\nAdjacency List Representation:\n";
        for (int i = 0; i < numNodes; i++) {
            cout << nodeLabels[i] << " -> ";
            for (int neighbor : adjList[i]) {
                cout << nodeLabels[neighbor] << " ";
            }
            cout << "\n";
        }
    }

    void printAdjMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void determineAndPrintNodes() {
        int E = -1, D = -1, B = -1, F = -1, A = -1, C = -1;

        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 1) { E = i; break; }
        }

        for (int j = 1; j < cols; j++) {
            if (matrix[E][j] != "0") { D = j; break; }
        }

        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 4) { B = i; break; }
        }

        for (int j = 1; j < cols; j++) {
            if (matrix[D][j] != "0" && j != E && j != B) { F = j; break; }
        }

        for (int i = 1; i < rows; i++) {
            int connections = 0;
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] != "0") connections++;
            }
            if (connections == 2) { A = i; break; }
        }

        for (int i = 1; i < rows; i++) {
            if (i != E && i != D && i != B && i != F && i != A) { C = i; break; }
        }

        cout << "\nNode A = " << matrix[A][0] << "\n";
        cout << "Node B = " << matrix[B][0] << "\n";
        cout << "Node C = " << matrix[C][0] << "\n";
        cout << "Node D = " << matrix[D][0] << "\n";
        cout << "Node E = " << matrix[E][0] << "\n";
        cout << "Node F = " << matrix[F][0] << "\n";

        string distance = matrix[B][C];
        cout << "\nDistance between B and C: " << distance << "\n";
    }
};

int main() {
    
    Graph graph;

    graph.printAdjList();
    graph.printAdjMatrix();
    graph.determineAndPrintNodes();

    return 0;
}

#include <iostream>
using namespace std;

class Graph {
private:
    int** adjMatrix;
    int maxVertices;
    int n;
    bool* visited;

public:
    Graph(int maxV, int currV) {
        maxVertices = maxV;
        n = currV;

        adjMatrix = new int*[maxVertices + 1];
        for (int i = 0; i <= maxVertices; i++) {
            adjMatrix[i] = new int[maxVertices + 1];
            for (int j = 0; j <= maxVertices; j++)
                adjMatrix[i][j] = 0;
        }

        visited = new bool[maxVertices + 1];
    }

    ~Graph() {
        for (int i = 0; i <= maxVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[] visited;
    }

    bool addVertex(int& v) {
        if (n == maxVertices)
            return false;
        n++;
        v = n;
        return true;
    }

    bool addEdge(int u, int v) {
        if (u < 1 || v < 1 || u > n || v > n)
            return false;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
        return true;
    }

    bool removeEdge(int u, int v) {
        if (u < 1 || v < 1 || u > n || v > n)
            return false;
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
        return true;
    }
};

int main() {
    Graph g(5, 0);
    int v;
    g.addVertex(v);
    g.addVertex(v);
    g.addEdge(1, 2);
    return 0;
}

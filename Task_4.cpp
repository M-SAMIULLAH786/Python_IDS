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

    Graph(const Graph& g) {
        maxVertices = g.maxVertices;
        n = g.n;

        adjMatrix = new int*[maxVertices + 1];
        for (int i = 0; i <= maxVertices; i++) {
            adjMatrix[i] = new int[maxVertices + 1];
            for (int j = 0; j <= maxVertices; j++)
                adjMatrix[i][j] = g.adjMatrix[i][j];
        }

        visited = new bool[maxVertices + 1];
    }

    ~Graph() {
        for (int i = 0; i <= maxVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[] visited;
    }
};

int main() {
    Graph g1(4, 4);
    Graph g2 = g1;
    return 0;
}

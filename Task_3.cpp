#include <iostream>
using namespace std;

class Graph {
private:
    int** adjMatrix;
    int maxVertices;
    int n;
    bool* visited;

    void DFS(int v) {
        cout << v << " ";
        visited[v] = true;

        for (int i = 1; i <= n; i++)
            if (adjMatrix[v][i] == 1 && !visited[i])
                DFS(i);
    }

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

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    void DFS() {
        for (int i = 1; i <= n; i++)
            visited[i] = false;

        int start;
        cin >> start;

        DFS(start);

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                DFS(i);
    }
};

int main() {
    Graph g(5, 5);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.DFS();
    return 0;
}

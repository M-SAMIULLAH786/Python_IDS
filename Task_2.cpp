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

    bool isEmpty() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (adjMatrix[i][j] == 1)
                    return false;
        return true;
    }

    bool isComplete() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && adjMatrix[i][j] == 0)
                    return false;
        return true;
    }

    void clear() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                adjMatrix[i][j] = 0;
    }

    void display() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    int Degree(int v) {
        if (v < 1 || v > n)
            return -1;
        int d = 0;
        for (int i = 1; i <= n; i++)
            if (adjMatrix[v][i] == 1)
                d++;
        return d;
    }
};

int main() {
    Graph g(4, 4);
    g.display();
    return 0;
}

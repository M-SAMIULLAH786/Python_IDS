//#include <iostream>
//#include <vector>
//#include <queue>
//using namespace std;
//
//// Function to find the number of centroids
//int permutations(int n, vector<vector<int>>& adj) {
//    vector<int> degree(n, 0);
//    vector<int> leaves;
//    for (int i = 0; i < n; i++) {
//        degree[i] = adj[i].size();
//        if (degree[i] == 1) {
//            leaves.push_back(i);
//        }
//    }
//
//    int remainingNodes = n;
//
//
//    while (remainingNodes > 2) {
//        vector<int> newLeaves;
//        for (int leaf : leaves) {
//            degree[leaf]--;
//            remainingNodes--;
//            for (int neighbor : adj[leaf]) {
//                degree[neighbor]--;
//                if (degree[neighbor] == 1) {
//                    newLeaves.push_back(neighbor);
//                }
//            }
//        }
//        leaves = newLeaves;
//    }
//
//    return leaves.size();
//}
//
//int main() {
//    int t;
//    cin >> t;
//    vector<int> result;
//    while (t--) {
//        int n;
//        cin >> n;
//
//        vector<vector<int>> adj(n);
//        for (int i = 0; i < n - 1; i++) {
//            int u, v;
//            cin >> u >> v;
//            adj[u].push_back(v);
//            adj[v].push_back(u);
//        }
//
//
//        int perms = permutations(n, adj);
//
//        result.push_back(perms);
//    }
//    for (int i = 0; i < result.size(); i++) {
//        if (i == result.size() - 1)
//            cout << result[i];
//        else
//            cout << result[i] << "\n";
//    }
//
//    return 0;
//}
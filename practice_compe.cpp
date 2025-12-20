#include <iostream>
#include <vector>
#include <set>
using namespace std;

void countCombinations(vector<set<int>>& departments, vector<bool>& used, int person, int& count) {
    if (person == departments.size()) {
        count++;
        return;
    }

    for (int dep : departments[person]) {
        if (!used[dep]) {
            used[dep] = true;
            countCombinations(departments, used, person + 1, count);
            used[dep] = false;
        }
    }
}

int main() {
    int cases;
    cin >> cases;
    vector<int> result;
    for (int c = 0; c < cases; c++) {
        int people;
        cin >> people;

        vector<set<int>> departments(people);
        int maxDepartmentId = 0;


        for (int i = 0; i < people; i++) {
            int depCount;
            cin >> depCount;
            for (int j = 0; j < depCount; j++) {
                int depId;
                cin >> depId;
                departments[i].insert(depId);
                maxDepartmentId = max(maxDepartmentId, depId);
            }
        }

        vector<bool> used(maxDepartmentId + 1, false);
        int count = 0;
        countCombinations(departments, used, 0, count);
        result.push_back(count);
    }
    for (int i = 0; i < cases; i++) {
        if (i == result.size() - 1) {
            cout << result[i];
        }
        else {
            cout << result[i] << "\n";

        }
    }
    return 0;
}
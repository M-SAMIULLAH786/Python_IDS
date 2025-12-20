#include<iostream>
#include<vector>
using namespace std;

int main() {
	int t, theta;
	cin >> t >> theta;
	vector<vector <int>> ans;
	for (int m = 0; m < t; m++) {
		int n;
		cin >> n;
		vector<int> x;
		for (int l = 0; l < n; l++) {
			int temp;
			cin >> temp;
			x.push_back(temp);
		}
		vector<int> delta;
		for (int i = 1; i < n; i++) {
			delta.push_back(abs(x[i] - x[i - 1]));
		}
		vector<int> res;
		for (int i = 1; i < n-1; i++) {
			res.push_back(abs(delta[i] - delta[i - 1]));
		}
		ans.push_back(res);
	}
	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++) {
			if (ans[i][j] < theta)
				cout << "0 ";
			else
				cout << "1 ";
		}
		cout << endl;
	}
}
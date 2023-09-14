#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int>parent;

bool cmp(vector<int>& road1, vector<int>& road2) {
	return road1[2] < road2[2];
}

int getParent(int num) {
	if (parent[num] == num) return num;
	return parent[num] = getParent(parent[num]);
}

void unionParent(int num1,int num2) {
	num1 = getParent(num1);
	num2 = getParent(num2);
	if (parent[num1] == parent[num2]) return;
	else if (parent[num1] < parent[num2]) parent[num2] = num1;
	else parent[num1] = num2;
}

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), M(0);
		cin >> N >> M;
		vector<vector<int>>roads(M, vector<int>(3, 0));
		parent = vector<int>(N + 1, 0);
		for (int idx = 1; idx <= N; ++idx) {
			parent[idx] = idx;
		}
		for (int idx = 0; idx < M; ++idx) {
			cin >> roads[idx][0] >> roads[idx][1] >> roads[idx][2];
		}
		sort(roads.begin(), roads.end(), cmp);
		
		int cnt(0), answer(0);
		for (int idx = 0; idx < M; ++idx) {
			int city1 = roads[idx][0];
			int city2 = roads[idx][1];
			int cost = roads[idx][2];
			if (getParent(city1) == getParent(city2)) continue;
			unionParent(city1, city2);
			++cnt;
			answer += cost;
			if (cnt == N - 1) break;
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;
}
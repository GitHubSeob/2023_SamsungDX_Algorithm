#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#define Y first
#define X second
#define ll long long
using namespace std;

vector<int>parent;
vector<vector<ll>>connect;

bool cmp(vector<ll>&island1, vector<ll>&island2) {
	return island1[2] < island2[2];
}

ll getParent(ll num) {	
	if (parent[num] == num) return num;
	return parent[num] = getParent(parent[num]);
}

void unionParent(ll num1, ll num2) {
	num1 = getParent(num1);
	num2 = getParent(num2);
	if (num1 == num2) return;
	else if (num1 < num2) parent[num2] = num1;
	else parent[num1] = num2;
}

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0);
		double E(0);
		cin >> N;

		vector<pair<ll, ll>>coord(N, { 0,0 });		
		connect = vector<vector<ll>>(N * (N - 1) / 2, vector<ll>(3, 0));		
		parent = vector<int>(N, 0);
		
		for (int idx = 0; idx < N; ++idx) {
			cin >> coord[idx].X;
			parent[idx] = idx;
		}

		for (int idx = 0; idx < N; ++idx) {
			cin >> coord[idx].Y;			
		}

		cin >> E;
		int cnt = 0;
		for (ll island1 = 0; island1 + 1 < N; ++island1) {
			for (ll island2 = island1+1; island2 < N; ++island2) {
				connect[cnt][0] = island1;
				connect[cnt][1] = island2;
				if (island1 == island2) continue;
				ll cost1 = abs(coord[island1].X - coord[island2].X);
				ll cost2 = abs(coord[island1].Y - coord[island2].Y);
				connect[cnt][2] = cost1 * cost1 + cost2 * cost2;
				++cnt;
			}
		}

		sort(connect.begin(), connect.end(), cmp);

		cnt = 0;
		double answer = 0;
		for (ll idx = 0; idx < N * (N - 1) / 2; ++idx) {
			ll island1 = connect[idx][0];
			ll island2 = connect[idx][1];
			ll cost = connect[idx][2];
			if (getParent(island1) == getParent(island2)) continue;
			unionParent(island1, island2);
			++cnt;
			answer += (E * cost);
			if (cnt == N - 1) break;
		}
		cout << fixed;
		cout.precision(0);
		cout << "#" << test_case << " " << answer << '\n';
	}
}
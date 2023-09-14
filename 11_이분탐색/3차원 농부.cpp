#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int>horses;
vector<int>cows;
int N, M, min_dist, cnt;

void binaryS(int node) {
	int left = 0, right = M - 1;

	while (left <= right) {
		int mid((left + right) / 2);

		int dist = abs(node - cows[mid]);
		if (dist == min_dist) {
			++cnt;
		}
		else if (dist < min_dist) {
			min_dist = dist;
			cnt = 1;
		}

		if (cows[mid] < node) {
			left = mid + 1;
		}
		else if (cows[mid] > node) {
			right = mid - 1;
		}
		else {
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int x1(0), x2(0);
		cin >> N >> M;
		cin >> x1 >> x2;

		horses = vector<int>(N, 0);
		cows = vector<int>(M, 0);
		cnt = 0;
		min_dist = 200000001;

		for (int idx = 0; idx < N; ++idx) {
			cin >> horses[idx];
		}
		for (int idx = 0; idx < M; ++idx) {
			cin >> cows[idx];
		}

		sort(cows.begin(), cows.end());

		for (int idx = 0; idx < N; ++idx) {
			binaryS(horses[idx]);
		}

		cout << "#" << test_case << " " << min_dist + abs(x2 - x1) << ' ' << cnt << '\n';
	}
}
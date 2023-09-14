#include <iostream>
#include <vector>
#include <algorithm>
#define pii pair<int, int>
#define V first
#define C second
using namespace std;

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), K(0);
		cin >> N >> K;
		vector<pii>item(N, { 0,0 });
		vector<int>knapsack(K + 1, 0);

		for (int idx = 0; idx < N; ++idx) {
			cin >> item[idx].V >> item[idx].C;
		}

		for (int idx = 0; idx < N; ++idx) {
			for (int weight = K; weight > 0; --weight) {
				if (weight - item[idx].V < 0) continue;
				knapsack[weight] = max(knapsack[weight], knapsack[weight - item[idx].V] + item[idx].C);
			}
		}

		cout << "#" << test_case << " " << knapsack[K] << '\n';
	}
}
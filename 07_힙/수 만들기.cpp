#include <iostream>
#include <queue>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), K(0), X(0), D(0), answer(0);
		X = 0, D = 1;
		cin >> N;

		int num[11];
		for (int idx = 0; idx < N; ++idx)	cin >> num[idx];
		cin >> K;

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
		pq.push({ 0,K });
		
		int cnt(0), target(0);
		while (!pq.empty()) {
			cnt = pq.top().first;
			target = pq.top().second;
			pq.pop();
			if (target == 0) {
				answer = cnt;
				break;
			}			

			pq.push({ cnt + target, 0 });
			for (int idx = 0; idx < N; ++idx) {
				pq.push({ cnt + target % num[idx], target / num[idx] });
			}
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
}
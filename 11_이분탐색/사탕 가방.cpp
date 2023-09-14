#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0);
		ll M(0), left(1),right(0), mid(0);
		cin >> N >> M;

		right = 1000000000000000000;
		vector<ll>candy(N, 0);
		for (int idx = 0; idx < N; ++idx) {
			cin >> candy[idx];
		}
		
		ll cnt(0);
		
		while (left <= right) {
			mid = (left + right) / 2;
			cnt = 0;
			for (int idx = 0; idx < N; ++idx) {
				cnt += candy[idx] / mid;
			}
			if (M <= cnt) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		cout << "#" << test_case << " " << right << '\n';
	}

}
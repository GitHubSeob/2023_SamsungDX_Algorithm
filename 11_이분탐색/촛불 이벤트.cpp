#include <iostream>
#define ll long long
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		ll answer(-1);
		ll N(0);
		cin >> N;
		ll left(0), right = (10000000000), mid(0);
		while (left <= right) {
			mid = (left + right) / 2;
			if (mid * mid + mid < N * 2) {
				left = mid + 1;
			}
			else if (mid * mid + mid == N * 2) {
				answer = mid;
				break;
			}
			else {
				right = mid - 1;
			}
		}

		cout << "#" << test_case << " " << answer << '\n';
	}
}
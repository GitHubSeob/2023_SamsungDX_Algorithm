#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll sum;

ll get_K(int K) {
	if (K == 1) return 2;

	ll ret(0);	
	ret = get_K(K / 2);
	ret = (ret * ret) % sum;

	if (K % 2 == 1) {
		ret *= 2;
		ret %= sum;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		ll A(0), B(0), K(0), answer(0);

		cin >> A >> B >> K;

		if (A > B) swap(A, B);
		sum = A + B;

		K = get_K(K);

		A = (A * K) % sum;
		B = sum - A;

		answer = min(A, B);

		cout << "#" << test_case << " " << answer << '\n';
	}

	return 0;
}
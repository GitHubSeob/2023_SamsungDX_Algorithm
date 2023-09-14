#include <iostream>
using namespace std;

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), M(0);
		bool flag(true);
		cin >> N >> M;

		for (int idx = 0; idx < N; ++idx) {
			if ((M & (1 << idx)) == 0) {
				flag = false;
				break;
			}
		}
		cout << "#" << test_case << " ";
		flag == true ? cout << "ON\n" : cout << "OFF\n";
	}
	return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), answer(0), visited_cnt(0), multiple(1), num(0);
		vector<bool>visited(10, false);
		cin >> N;

		while (visited_cnt < 10) {
			num = multiple * N;
			answer = num;
			while (num > 0) {
				if (visited[num % 10] == false) {
					visited[num % 10] = true;
					++visited_cnt;
				}
				num /= 10;
			}
			++multiple;
		}

		cout << "#" << test_case << " " << answer << '\n';
	}
}
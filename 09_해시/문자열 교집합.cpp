#include <iostream>
#include <unordered_set>
using namespace std;

unordered_set<string> NM_set;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), M(0), answer(0);
		string input("");
		cin >> N >> M;
		NM_set = unordered_set<string>();

		for (int idx = 0; idx < N; ++idx) {
			cin >> input;
			NM_set.insert(input);
		}

		for (int idx = 0; idx < M; ++idx) {
			cin >> input;
			if (NM_set.find(input) != NM_set.end()) {
				++answer;
			}
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
}
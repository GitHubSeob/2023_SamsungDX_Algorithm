#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		string s1(""), s2("");
		cin >> s1 >> s2;
		vector<vector<int>>DP(s2.size() + 1, vector<int>(s1.size() + 1, 0));
		for (int idx2 = 1; idx2 <= s2.size(); ++idx2) {
			for (int idx = 1; idx <= s1.size(); ++idx) {
				if (s2[idx2 - 1] == s1[idx - 1]) {
					DP[idx2][idx] = DP[idx2 - 1][idx - 1] + 1;
				}
				else {
					DP[idx2][idx] = max(DP[idx2][idx - 1], DP[idx2 - 1][idx]);
				}
			}
		}
		int answer = DP[s2.size()][s1.size()];
		cout << "#" << test_case << " " << answer << '\n';
	}
}
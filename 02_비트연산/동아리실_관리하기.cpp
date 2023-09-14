#include <iostream>
#include <string>
#include <vector>
#include <map>
#define ll long long
#define DIV 1000000007
using namespace std;

int main() {
	int T(0);
	cin >> T;
	map<char, int>group;
	group.insert({ 'A', 8 });
	group.insert({ 'B', 4 });
	group.insert({ 'C', 2 });
	group.insert({ 'D', 1 });

	for (int test_case = 1; test_case <= T; ++test_case) {
		vector<vector<ll>>DP(10000, vector<ll>(16, 0));
		int binary(0);
		ll answer(0);
		string input("");
		cin >> input;

		for (int idx = 0; idx < input.size(); ++idx) {
			if (idx == 0) {
				for (binary = 1; binary <= 15; ++binary) {
					if (group[input[0]] & binary && group['A'] & binary) {
						DP[0][binary] = 1;
					}
				}
			}
			else {
				for (int bin_f = 1; bin_f <= 15; ++bin_f) {
					if (DP[idx - 1][bin_f] == 0) continue;
					for (int bin_b = 1; bin_b <= 15; ++bin_b) {
						if ((bin_b & group[input[idx]]) != group[input[idx]]) continue;
						if (((bin_f & group[input[idx]]) == group[input[idx]]) ||
							((bin_f & bin_b) > 0)) {
							DP[idx][bin_b] += DP[idx - 1][bin_f];
							DP[idx][bin_b] %= DIV;
						}
					}
				}
			}
		}

		for (int idx = 1; idx <= 15; ++idx) {
			answer += DP[input.size() - 1][idx];
			answer %= DIV;
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;
}
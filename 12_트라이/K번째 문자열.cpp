#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int K(0);
		string input(""), str("");
		vector<string>answer;
		answer.clear();

		cin >> K >> input;

		for (int left = 0; left < input.size(); ++left) {
			str.clear();
			for (int right = left; right < input.size(); ++right) {
				str += input[right];
				answer.push_back(str);
			}
		}
		
		sort(answer.begin(), answer.end());
		answer.erase(unique(answer.begin(), answer.end()), answer.end());

		cout << "#" << test_case << " ";
		if (answer.size() <= K) cout << "none\n";
		else cout << answer[K - 1] << '\n';

	}
}
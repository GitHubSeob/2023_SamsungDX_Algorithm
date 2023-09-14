#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;

int main() {
	for (int test_case = 1; test_case <= 10; ++test_case) {
		int node_cnt(0);
		bool answer(true);
		cin >> node_cnt;
		cin.ignore();
		
		string input("");
		vector<vector<int>>tree(node_cnt + 1);
		
		for (int idx = 0; idx < node_cnt; ++idx) {
			int node(0), left(0), right(0);
			string s("");
			getline(cin, input);

			istringstream iss(input);
			iss >> node >> s >> left >> right;
			if (left == 0 && right == 0) {				
				if (!isdigit(s[0])) answer = false;
			}
			else {
				if (isdigit(s[0])) answer = false;
			}
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
}
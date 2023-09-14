#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Trie {
	int child[26];
	bool is_terminal;

	Trie() {
		memset(child, -1, sizeof(child));
		is_terminal = false;
	}
};

vector<Trie>nodes(400);
vector<string>answer;

void insert(string str) {
	int node_id(0);
	string sub;
	sub = str;
	for (int idx = 0; idx < str.size(); ++idx) {
		if (nodes[node_id].child[str[idx] - 'a'] == -1) {
			nodes[node_id].child[str[idx] - 'a'] = nodes.size();
			nodes.emplace_back();			
		}
		node_id = nodes[node_id].child[str[idx] - 'a'];
		sub.erase(0, 1);
		if (!sub.empty())
			answer.push_back(sub);
	}
	nodes[node_id].is_terminal = true;
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int K(0);
		string input("");

		cin >> K >> input;

		answer.clear();

		cout << "#" << test_case << " ";
		if (input.size() < K) cout << "none\n";
		else {
			answer.push_back(input);
			insert(input);			
			sort(answer.begin(), answer.end());

			cout << answer[K-1] << '\n';
		}
	}
}
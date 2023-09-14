#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void inorder(int node, vector<vector<int>>tree, vector<string>alp) {

	if (tree[node].size() > 0) {
		inorder(tree[node][0], tree, alp);
	}
	cout << alp[node];
	if (tree[node].size() > 1) {
		inorder(tree[node][1], tree, alp);
	}
}

int main() {
	for (int test_case = 1; test_case <= 10; ++test_case) {
		int node_cnt(0);
		cin >> node_cnt;
		cin.ignore();

		vector<vector<int>>tree(node_cnt + 1);
		vector<string>alp(node_cnt + 1, "");

		for (int idx = 0; idx < node_cnt; ++idx) {			
			string input("");			
			getline(cin, input);

			istringstream iss(input);
			string alpabet("");
			int node(0), left(0), right(0);
				
			iss >> node >> alpabet >> left >> right;
			
			alp[node] = alpabet;
			if (left != 0) tree[node].push_back(left);
			if (right != 0) tree[node].push_back(right);					
		}

		cout << "#" << test_case << ' ';
		inorder(1, tree, alp);
		cout << '\n';
	}
}
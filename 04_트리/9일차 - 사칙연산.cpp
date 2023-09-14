#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int inorder(int node, vector<vector<int>>tree, vector<string>vertex) {
	int value1(0), value2(0);

	if (tree[node].size() > 0) {
		value1 = inorder(tree[node][0], tree, vertex);
	}
	if (tree[node].size() > 1) {
		value2 = inorder(tree[node][1], tree, vertex);
	}

	if (vertex[node] == "+") {
		return value1 + value2;
	}
	else if (vertex[node] == "-") {
		return value1 - value2;
	}
	else if (vertex[node] == "*") {
		return value1 * value2;
	}
	else if (vertex[node] == "/") {
		return value1 / value2;
	}

	return stoi(vertex[node]);
}

int main() {
	for (int test_case = 1; test_case <= 10; ++test_case) {
		int node_cnt(0);
		cin >> node_cnt;		

		vector<vector<int>>tree(node_cnt + 1);
		vector<string>vertex(node_cnt + 1);

		cin.ignore();
		for (int idx = 0; idx < node_cnt; ++idx) {			
			int node(0), left(0), right(0);

			string s(""), input("");
			getline(cin, input);
			istringstream iss(input);

			iss >> node >> s >> left >> right;
			vertex[node] = s;
			
			if (left != 0) tree[node].push_back(left);
			if (right != 0) tree[node].push_back(right);

			
		}		
		cout << "#" << test_case << ' ';
		cout << inorder(1, tree, vertex) << '\n';

	}
}
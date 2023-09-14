#include <iostream>
#include <vector>
using namespace std;

int node1, node2;
vector<vector<int>>tree;
vector<int>answer(2, 0);

vector<int> postorder(int node) {
	int node1_dist(0), node2_dist(0);
	vector<int>ret(3, 0);
	
	if (node == node1) {
		ret[1] = 1;
	}
	if (node == node2) {
		ret[2] = 1;
	}
	if (tree[node].size() == 0) {
		ret[0] = 1;
		return ret;
	}
	
	if (tree[node].size() > 0) {
		vector<int>temp = postorder(tree[node][0]);
		ret[0] += temp[0];
		ret[1] += temp[1];
		ret[2] += temp[2];
	}
	if (tree[node].size() > 1) {
		vector<int>temp = postorder(tree[node][1]);
		ret[0] += temp[0];
		ret[1] += temp[1];
		ret[2] += temp[2];
	}
	ret[0] += 1;	
	
	if (ret[1] >= 1 && ret[2] >= 1) {		
		answer[0] = node;
		answer[1] = ret[0];
		ret[1] = 0;
		ret[2] = 0;
	}
	
	return ret;
}

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int V(0),E(0), parent(0), child(0);		
		cin >> V >> E >> node1 >> node2;
		tree = vector<vector<int>>(V + 1);

		for (int idx = 0; idx < E; ++idx) {
			cin >> parent >> child;			
			tree[parent].push_back(child);
		}

		postorder(1);
		cout << "#" << test_case << " " << answer[0] << " " << answer[1] << '\n';
	}
}
#include <vector>
#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
#define MAX 100001
#define ll long long
using namespace std;

int max_level;
int parent[MAX][20];
int depth[MAX];
ll dist;

int LCA(int node1, int node2) {
	if (depth[node1] < depth[node2]) {
		swap(node1, node2);
	}
	int idx = 0;
	while (depth[node1] != depth[node2]) {
		++idx;
		if ((depth[node1] - (1 << idx)) < depth[node2]) {
			node1 = parent[node1][idx - 1];
			idx = 0;
		}
	}

	while (node1 != node2) {
		idx = 1;
		while (parent[node1][idx] != parent[node2][idx]) {
			++idx;
		}
		node1 = parent[node1][idx - 1];
		node2 = parent[node2][idx - 1];
	}

	return node1;
}

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0);
		cin >> N;

		max_level = (int)log2(MAX);
		vector<vector<int>>tree(MAX);
		memset(parent, 0, sizeof(parent));
		memset(depth, 0, sizeof(depth));

		for (int idx = 2; idx <= N; ++idx) {
			int node(0);
			cin >> node;
			tree[node].push_back(idx);
			parent[idx][0] = node;
		}

		for (int node = 2; node <= N; ++node) {
			cout << "노드: " << node << " ";
			for (int idx = 1; idx < max_level; ++idx) {
				int parent_node = parent[node][idx - 1];
				if (parent[parent_node][idx - 1] == 0) break;
				parent[node][idx] = parent[parent_node][idx - 1];
				cout << parent[node][idx] << ' ';
			}
			cout << '\n';
		}

		queue<int>q;
		q.push(1);
		int prev_node(1);
		dist = 0;
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int idx = 0; idx < tree[node].size(); ++idx) {
				int child_node = tree[node][idx];
				depth[child_node] = depth[node] + 1;
				q.push(child_node);
			}

			int lca_node = LCA(prev_node, node);
			dist += depth[prev_node] + depth[node] - depth[lca_node] * 2;
			prev_node = node;
		}


		cout << "#" << test_case << " " << dist << '\n';
	}
}
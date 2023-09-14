#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 1000000001
#define MIN -1
#define ll long long
using namespace std;

vector<ll>arr;
vector<ll>max_tree;
vector<ll>min_tree;;

ll init_max(int node, int start, int end){
	if (start == end)  return max_tree[node] = arr[start];

	else if (start != end) {
		int mid((start + end) / 2);
		
		max_tree[node] = max(init_max(node * 2, start, mid), init_max(node * 2 + 1, mid + 1, end));
		return max_tree[node];
	}	
}

ll init_min(int node, int start, int end) {
	if (start == end)  return min_tree[node] = arr[start];

	else if (start != end) {
		int mid((start + end) / 2);

		min_tree[node] = min(init_min(node * 2, start, mid), init_min(node * 2 + 1, mid + 1, end));
		return min_tree[node];
	}
}


ll update_min(int node, int start, int end, int idx, ll val) {
	if (idx < start || end < idx) return min_tree[node];
	if (start == end && start == idx) return min_tree[node] = val;	

	if (start != end) {
		int mid((start + end) / 2);
		min_tree[node] = min(update_min(node * 2, start, mid, idx, val), update_min(node * 2 + 1, mid + 1, end, idx, val));
	}

	return min_tree[node];
}

ll update_max(int node, int start, int end, int idx, ll val) {
	if (idx < start || end < idx) return max_tree[node];
	if (start == end && start == idx) return max_tree[node] = val;

	if (start != end) {
		int mid((start + end) / 2);
		max_tree[node] = max(update_max(node * 2, start, mid, idx, val), update_max(node * 2 + 1, mid + 1, end, idx, val));
	}

	return max_tree[node];
}

ll search_min(int node, int start, int end, int left, int right) {
	if (start > right || end < left) return MAX;
	else if (left <= start && right >= end) return min_tree[node];
	else {
		int mid((start + end) / 2);
		return min(search_min(node * 2, start, mid, left, right),
			search_min(node * 2 + 1, mid + 1, end, left, right));
	}	
}

ll search_max(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return MIN;
	else if (left <= start && end <= right) return max_tree[node];
	else {
		int mid((start + end) / 2);
		return max(search_max(node * 2, start, mid, left, right),
			search_max(node * 2 + 1, mid + 1, end, left, right));
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;

	int N(0), Q(0);
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N >> Q;

		arr = vector<ll>(N + 1, 0);
		int tree_h = (int)ceil(log2(N));
		int tree_size = (1 << (tree_h + 1));
		max_tree = vector<ll>(tree_size, 0);
		min_tree = vector<ll>(tree_size, 0);

		for (int idx = 1; idx <= N; ++idx) {
			cin >> arr[idx];
		}

		cout << "#" << test_case << ' ';
		init_max(1, 1, N);
		init_min(1, 1, N);

		int a(0), b(0), c(0);
		for (int idx = 0; idx < Q; ++idx) {
			cin >> a >> b >> c;
			++b;
			if (a == 0) {
				update_max(1, 1, N, b, c);
				update_min(1, 1, N, b, c);
			}
			else if (a == 1) {				
				cout << search_max(1, 1, N, b, c) - search_min(1, 1, N, b, c) << ' ';
			}
		}		
		cout << '\n';
	}
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;

vector<ll>odd_arr;
vector<ll>even_arr;
vector<ll>odd_tree;
vector<ll>even_tree;;

ll init_odd(int node, int start, int end) {
	if (start == end) return odd_tree[node] = odd_arr[start];

	if (start != end) {
		int mid((start + end) / 2);
		odd_tree[node] = init_odd(node * 2, start, mid);
		odd_tree[node] += init_odd(node * 2 + 1, mid + 1, end);
	}
	return odd_tree[node];
}

ll init_even(int node, int start, int end) {
	if (start == end) return even_tree[node] = even_arr[start];

	if (start != end) {
		int mid((start + end) / 2);
		even_tree[node] = init_even(node * 2, start, mid);
		even_tree[node] += init_even(node * 2 + 1, mid + 1, end);
	}
	return even_tree[node];
}


void update_odd(int node, int start, int end, int idx, ll diff) {
	if (idx < start || end < idx) return;
	odd_tree[node] += diff;

	if (start != end) {
		int mid((start + end) / 2);
		update_odd(node * 2, start, mid, idx, diff);
		update_odd(node * 2 + 1, mid + 1, end, idx, diff);
	}
}

void update_even(int node, int start, int end, int idx, ll diff) {
	if (idx < start || end < idx) return;
	even_tree[node] += diff;

	if (start != end) {
		int mid((start + end) / 2);
		update_even(node * 2, start, mid, idx, diff);
		update_even(node * 2 + 1, mid + 1, end, idx, diff);
	}
}


ll sum_odd(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return odd_tree[node];

	ll ret(0);
	int mid((start + end) / 2);
	ret = sum_odd(node * 2, start, mid, left, right);
	ret += sum_odd(node * 2 + 1, mid + 1, end, left, right);

	return ret;
}

ll sum_even(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return even_tree[node];

	ll ret(0);
	int mid((start + end) / 2);
	ret = sum_even(node * 2, start, mid, left, right);
	ret += sum_even(node * 2 + 1, mid + 1, end, left, right);

	return ret;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;

	int N(0), Q(0);
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N >> Q;

		odd_arr = vector<ll>(N + 1, 0);
		even_arr = vector<ll>(N + 1, 0);
		int tree_h = (int)ceil(log2(N));
		int tree_size = (1 << (tree_h + 1));
		odd_tree = vector<ll>(tree_size, 0);
		even_tree = vector<ll>(tree_size, 0);

		for (int idx = 1; idx <= N; ++idx) {
			if (idx % 2 == 1) cin >> odd_arr[idx];
			else if (idx % 2 == 0) cin >> even_arr[idx];			
		}

		cout << "#" << test_case << ' ';
		init_odd(1, 1, N);
		init_even(1, 1, N);

		int a(0), b(0), c(0);		
			
		for (int idx = 0; idx < Q; ++idx) {
			cin >> a >> b >> c;
			++b;
			if (a == 0) {
				if (b % 2 == 1) {
					update_odd(1, 1, N, b, c - odd_arr[b]);
					odd_arr[b] = c;
				}
				else if (b % 2 == 0) {
					update_even(1, 1, N, b, c - even_arr[b]);
					even_arr[b] = c;
				}
			}
			else if (a == 1) {
				if (b % 2 == 1) {
					cout << sum_odd(1, 1, N, b, c) - sum_even(1, 1, N, b, c) << ' ';
				}
				else if (b % 2 == 0) {
					cout << sum_even(1, 1, N, b, c) - sum_odd(1, 1, N, b, c) << ' ';
				}
			}
		}
		cout << '\n';
	}
}
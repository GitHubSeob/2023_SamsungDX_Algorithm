#include <iostream>
using namespace std;

string name[20000];
string tmp[20000];

void mergesort(int left, int right) {
	if (left >= right) return;
	int mid = (left + right) / 2;

	mergesort(left, mid);
	mergesort(mid + 1, right);

	int idx = left, m = mid + 1;	

	for (int i = left; i <= right; ++i) {
		tmp[i] = name[i];
	}

	while (left <= mid || m <= right) {
		if (left > mid) {
			while (m <= right) {
				name[idx++] = tmp[m++];
			}
			break;
		}
		else if (m > right) {
			while (left <= mid) {
				name[idx++] = tmp[left++];
			}
			break;
		}
		else {
			if (tmp[left].size() == tmp[m].size()) {
				if (tmp[left] < tmp[m]) {
					name[idx++] = tmp[left++];
				}
				else {
					name[idx++] = tmp[m++];
				}
			}
			else {
				if (tmp[left].size() < tmp[m].size()) {
					name[idx++] = tmp[left++];
				}
				else {
					name[idx++] = tmp[m++];
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	int T(0), answer(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0);
		cin >> N;

		for (int idx = 0; idx < 20000; ++idx) {
			name[idx].clear();
			tmp[idx].clear();
		}		

		for (int idx = 0; idx < N; ++idx) {
			cin >> name[idx];
		}		

		mergesort(0, N - 1);

		cout << "#" << test_case << '\n';
		cout << name[0] << '\n';
		for (int idx = 1; idx < N; ++idx) {
			if (name[idx] == name[idx - 1]) continue;
			cout << name[idx] << '\n';
		}
	}
}
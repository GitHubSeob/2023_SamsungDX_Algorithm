#include <queue>
#include <iostream>
using namespace std;

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		cout << "#" << test_case << " ";
		int N(0), cmd(0);
		cin >> N;
		priority_queue<int>pq;
		for (int idx = 0; idx < N; ++idx) {
			int input(0);
			cin >> cmd;
			if (cmd == 1) {
				cin >> input;
				pq.push(input);
			}
			else if (cmd == 2) {
				if (pq.empty()) cout << "-1 ";
				else {
					cout << pq.top() <<" ";
					pq.pop();
				}
			}
		}
		cout << '\n';
	}
}
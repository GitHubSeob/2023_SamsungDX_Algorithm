#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#define ll long long
#define DIV 20171109
using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), num(0), left_num(0), right_num(0);
		ll answer(0);

		priority_queue<int>left;
		priority_queue<int, vector<int>, greater<int>>right;

		cin >> N >> num;

		left.push(num);
		right.push(1000000001);
		int num1(0), num2(0);

		for (int idx = 0; idx < N; ++idx) {
			cin >> num1 >> num2;

			left_num = left.top();
			left.pop();

			right_num = right.top();
			right.pop();
			int number[4] = { left_num,right_num,num1,num2 };

			sort(number, number + 4);

			left.push(number[0]);
			left.push(number[1]);

			right.push(number[2]);
			right.push(number[3]);

			answer += left.top();
			answer %= DIV;
		}
		cout << "#" << test_case << " " << answer << '\n';
	}
}
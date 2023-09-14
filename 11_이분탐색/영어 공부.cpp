#include <iostream>
#include <cstring>
using namespace std;
int N, P;
bool days[1000001];
int answer;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), P(0), day(0), end(0);
		cin >> N >> P;
		answer = P + 1;
		
		memset(days, false, sizeof(days));

		for (int idx = 0; idx < N; ++idx) {
			cin >> day;
			days[day] = true;			
		}

		int left(1), right(1);
		while (right <= day) {			
			if (days[right] == true) {
				++right;
			}
			else if (days[right] == false) {
				if (P > 0) {
					--P;
					++right;
				}
				else if (P == 0) {
					if (days[left] == true) {						
						++left;
					}
					else if (days[left] == false) {
						++left;
						++P;
					}
				}
			}
			answer = max(answer, right - left + P);
		}


		cout << "#" << test_case << " " << answer << '\n';
	}

}
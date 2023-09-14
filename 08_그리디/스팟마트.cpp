#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N_snack[3002];
int M_snack[102];

int DP[3002][102][102][2];

int N, M;
int pick(int N_idx, int M_idx, int waste, int prev) {	
	int ret(0);	
	if (DP[N_idx][M_idx][waste][prev] != -1) return DP[N_idx][M_idx][waste][prev];

	if (prev == 0) {
		if (N_idx < N) {
			ret = max(ret, pick(N_idx + 1, M_idx, waste, 1) + N_snack[N_idx]);
			ret = max(ret, pick(N_idx + 1, M_idx, waste, 0));
		}
		if (M_idx + waste < M) {
			ret = max(ret, pick(N_idx, M_idx + 1, waste, 1) + M_snack[M_idx]);
			ret = max(ret, pick(N_idx, M_idx, waste + 1, 0));
		}

	}
	else if (prev == 1) {
		if (N_idx < N) {
			ret = max(ret, pick(N_idx + 1, M_idx, waste, 0));
		}
		if (M_idx + waste < M) {
			ret = max(ret, pick(N_idx, M_idx, waste + 1, 0));
		}
	}

	DP[N_idx][M_idx][waste][prev] = ret;
	return ret;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int answer(0);

		memset(N_snack, 0, sizeof(N_snack));
		memset(M_snack, 0, sizeof(M_snack));
		memset(DP, -1, sizeof(DP));

		cin >> N;		
		for (int idx = 0; idx < N; ++idx) {
			cin >> N_snack[idx];
		}

		cin >> M;		
		for (int idx = 0; idx < M; ++idx) {
			cin >> M_snack[idx];
		}
		sort(M_snack, M_snack + 102, greater<int>());

		answer = pick(0,0,0,0);

		cout << "#" << test_case << " " << answer << '\n';
	}
}
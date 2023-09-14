#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define ll long long
#define power_val 3
#define MOD 1000000007
using namespace std;

ll p1[2000][2000];
ll p2[2000][2000];
ll sum[2000][2000];
ll p_sum[2000][2000];
ll power[4000000];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {

		int H(0), W(0), N(0), M(0), answer(0);
		cin >> H >> W >> N >> M;

		memset(p1, 0, sizeof(p1));
		memset(p2, 0, sizeof(p2));
		memset(sum, 0, sizeof(sum));
		memset(p_sum, 0, sizeof(p_sum));
		memset(power, 0, sizeof(power));

		ll p1_val(0);

		string input("");
		for (int y = 0; y < H; ++y) {
			cin >> input;
			for (int x = 0; x < input.size(); ++x) {
				p1[y][x] = input[x] == 'o' ? 1 : 0;
			}
		}

		for (int y = 0; y < N; ++y) {
			cin >> input;
			for (int x = 0; x < input.size(); ++x) {
				p2[y][x] = input[x] == 'o' ? 1 : 0;
			}
		}

		power[0] = 1;
		for (int idx = 1; idx < N * M; ++idx) {
			power[idx] = (power[idx - 1] * power_val) % MOD;
		}

		for (int y = 0; y < H; ++y) {
			for (int x = 0; x < W; ++x) {
				p1_val = (p1_val + p1[y][x] * power[y * M + x]) % MOD;
			}
		}

		for (int y = 0; y < N; ++y) {
			for (int x = 0; x < M; ++x) {
				if (x >= 1) sum[y][x] += sum[y][x - 1];
				if (y >= 1) sum[y][x] += sum[y - 1][x];
				sum[y][x] += (p2[y][x] * power[y * M + x]) % MOD;
				if (y >= 1 && x >= 1)
					sum[y][x] -= sum[y - 1][x - 1];
			}
		}


		for (int y = 0; y + H <= N; ++y) {
			for (int x = 0; x + W <= M; ++x) {
				if (y == 0 && x == 0) {
					p_sum[y][x] = sum[y + H - 1][x + W - 1];
				}
				else if (y == 0) {
					p_sum[y][x] = sum[y + H - 1][x + W - 1] - sum[y + H - 1][x - 1];
				}
				else if (x == 0) {
					p_sum[y][x] = sum[y + H - 1][x + W - 1] - sum[y - 1][x + W - 1];
				}
				else {
					p_sum[y][x] = sum[y + H - 1][x + W - 1] - sum[y + H - 1][x - 1] - sum[y - 1][x + W - 1] + sum[y - 1][x - 1];
				}
				p_sum[y][x] %= MOD;
				if ((p1_val * power[y * M + x]) % MOD == p_sum[y][x]) ++answer;

			}
		}

		cout << "#" << test_case << " " << answer << '\n';
	}
}
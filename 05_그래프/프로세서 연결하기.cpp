#include <iostream>
#include <vector>
#include <algorithm>
#define Y first
#define X second
using namespace std;

vector<vector<int>>board;
vector<pair<int, int>>mexynos;
int max_cnt, max_wire;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int N;

void DFS(int idx, int cnt) {
	int wire_cnt(0);
	if (idx == mexynos.size()) {
		if (max_cnt < cnt) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (board[i][j] == 2) ++wire_cnt;
				}
			}

			max_cnt = cnt;
			max_wire = wire_cnt;
		}
		else if (max_cnt == cnt) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (board[i][j] == 2) ++wire_cnt;
				}
			}
			max_wire = min(max_wire, wire_cnt);
		}

		return;
	}

	int y(mexynos[idx].Y), x(mexynos[idx].X);

	if (idx + 1 <= mexynos.size())
		DFS(idx + 1, cnt);

	for (int idx2 = 0; idx2 < 4; ++idx2) {
		bool flag(true);
		int ny = y;
		int nx = x;
		while (1) {
			ny += dy[idx2];
			nx += dx[idx2];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N) break;
			if (board[ny][nx] == 1 || board[ny][nx] == 2) {
				flag = false;
				while (1) {
					ny -= dy[idx2];
					nx -= dx[idx2];
					if (ny == y && nx == x) break;
					board[ny][nx] = 0;
				}
				break;
			}
			board[ny][nx] = 2;
		}
		if (flag) {
			if (mexynos.size() - 1 - idx + cnt + 1 >= max_cnt) {
				DFS(idx + 1, cnt + 1);
			}
			while (1) {
				ny -= dy[idx2];
				nx -= dx[idx2];
				if (ny == y && nx == x) break;
				board[ny][nx] = 0;
			}
		}
	}
}


int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int y(0), x(0);
		max_cnt = 0;
		max_wire = 145;
		cin >> N;
		board = vector<vector<int>>(N, vector<int>(N, 0));
		mexynos = vector<pair<int, int>>();

		for (y = 0; y < N; ++y) {
			for (x = 0; x < N; ++x) {
				cin >> board[y][x];
				if (board[y][x] == 1) {
					if (x == 0 || y == 0 || x == N - 1 || y == N - 1) continue;
					mexynos.push_back({ y,x });
				}
			}
		}

		DFS(0, 0);

		cout << "#" << test_case << " " << max_wire << "\n";
	}
}
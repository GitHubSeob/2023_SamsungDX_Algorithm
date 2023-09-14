#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define Y front().first
#define X front().second
#define MAX 300
#define pii pair<int, int> 
using namespace std;


int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

char board[MAX][MAX];
bool visited[MAX][MAX];
int zero[MAX * MAX][2];

int N, answer, zero_idx;

void DFS(int y, int x) {
	for (int idx = 0; idx < 8; ++idx) {
		int ny(y + dy[idx]);
		int nx(x + dx[idx]);
		if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
		if (visited[ny][nx] == true) continue;
		visited[ny][nx] = true;
		if (board[ny][nx] != '*') --answer;
		if (board[ny][nx] == '0') {
			DFS(ny, nx);
		}
	}
}

void getNumber() {
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			int number(0);
			if (board[y][x] == '*') continue;
			for (int idx = 0; idx < 8; ++idx) {
				int ny(y + dy[idx]);
				int nx(x + dx[idx]);
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				if (board[ny][nx] == '*') ++number;
			}

			board[y][x] = number + '0';

			if (board[y][x] == '0') {
				zero[zero_idx][0] = y;
				zero[zero_idx][1] = x;
				++zero_idx;
			}
		}
	}
}

void init() {
	memset(board, ' ', sizeof(board));
	memset(zero, 0, sizeof(zero));
	memset(visited, false, sizeof(visited));
	answer = N * N;
	zero_idx = 0;
}


int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N;
		string input("");

		init();

		for (int idx = 0; idx < N; ++idx) {
			cin >> input;
			for (int idx2 = 0; idx2 < N; ++idx2) {
				board[idx][idx2] = input[idx2];
				if (input[idx2] == '*') --answer;
			}
		}

		getNumber();

		for (int idx = 0; idx < zero_idx; ++idx) {
			int y(zero[idx][0]);
			int x(zero[idx][1]);
			if (visited[y][x] == false) {
				visited[y][x] = true;
				DFS(y, x);
			}
		}

		cout << "#" << test_case << " " << answer << '\n';
	}
}
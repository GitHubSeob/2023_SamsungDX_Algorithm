#include <iostream>
#define MAX 101
#define INF 100001
using namespace std;

int map[MAX][MAX];
int visited[MAX][MAX];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { -1,1,0,0 };
int N;


void DFS(int y, int x, int time) {
	int ny(0), nx(0), new_time(0);

	for (int idx = 0; idx < 4; ++idx) {
		ny = y + dy[idx];
		nx = x + dx[idx];
		new_time = time + map[ny][nx];
		if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
		if (new_time >= visited[ny][nx]) continue;
		visited[ny][nx] = new_time;
		DFS(ny, nx, new_time);
	}
}

void init() {
	for (int y = 0; y < MAX; ++y) {
		for (int x = 0; x < MAX; ++x) {
			map[y][x] = -1;
			visited[y][x] = INF;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N;

		init();

		for (int y = 0; y < N; ++y) {
			string input("");
			cin >> input;
			for (int x = 0; x < input.size(); ++x) {
				map[y][x] = input[x]-'0';
			}
		}

		DFS(0, 0, 0);
		if (N - 1 < MAX)
			cout << "#" << test_case << " " << visited[N - 1][N - 1] << '\n';
	}
}
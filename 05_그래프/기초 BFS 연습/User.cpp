int visited[10][10];
int board[10][10];

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void bfs_init(int map_size, int map[10][10]) {
	for (int y = 0; y < map_size; ++y) {
		for (int x = 0; x < map_size; ++x) {
			board[y][x] = map[y][x];
		}
	}
}
int bfs(int x1, int y1, int x2, int y2) {
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			visited[y][x] = false;
		}
	}
	--x1, --y1, --x2, --y2;
	int queue[100][3] = { 0, };
	int rear(-1), front(-1);
	queue[0][0] = y1;
	queue[0][1] = x1;
	queue[0][2] = 0;
	++rear;
	visited[y1][x1] = true;
	while (front != rear) {
		++front;
		int y = queue[front][0];
		int x = queue[front][1];
		int dist = queue[front][2];

		for (int idx = 0; idx < 4; ++idx) {
			int ny = y + dy[idx];
			int nx = x + dx[idx];
			if (ny < 0 || ny>9 || nx < 0 || nx>9) continue;
			if (board[ny][nx] == 1) continue;
			if (visited[ny][nx] == true) continue;
			visited[ny][nx] = true;
			if (ny == y2 && nx == x2)	return dist + 1;

			++rear;
			queue[rear][0] = ny;
			queue[rear][1] = nx;
			queue[rear][2] = dist + 1;

		}
	}
	return -1;
}

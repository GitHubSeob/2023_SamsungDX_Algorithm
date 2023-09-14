int graph[100][5] = { 0, };
int cnt[100] = { 0, };
bool visited[100] = { false, };

int find(int k, int node);

void dfs_init(int N, int path[100][2])
{
	for (int y = 1; y < 100; ++y) {
		visited[y] = false;
		for (int x = 0; x < cnt[y]; ++x) {
			graph[y][x] = 0;
		}
		cnt[y] = 0;
	}

	for (int idx = 0; idx < N; ++idx) {
		if (path[idx][0] == 0) continue;
		graph[path[idx][0]][cnt[path[idx][0]]++] = path[idx][1];
	}
}

int dfs(int n)
{
	for (int idx = 1; idx < 100; ++idx) {
		visited[idx] = false;
	}
	return find(n, n);
}

int find(int k, int node) {
	int num = -1;
	for (int idx = 0; idx < cnt[node]; ++idx) {
		if (visited[graph[node][idx]] == false) {
			visited[graph[node][idx]] = true;
			if (k < graph[node][idx]) {
				return graph[node][idx];
			}
			num = find(k, graph[node][idx]);
			if (num != -1) return num;
		}
	}

	return num;
}
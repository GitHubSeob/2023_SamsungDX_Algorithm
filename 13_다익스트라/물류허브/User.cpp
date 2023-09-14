#include <unordered_map>
#include <queue>
#define MAX 601
#define INF 999999
#define pii pair<int, int>
using namespace std;

unordered_map<int, int>num;
vector<vector<pii>>costs;
int min_cost[MAX][MAX];
priority_queue<pii>pq;
int node_num;

int init(int N, int sCity[], int eCity[], int mCost[]) {
	node_num = 0;

	costs = vector<vector<pii>>(MAX);
	num = unordered_map<int, int>();

	for (int idx = 1; idx < MAX; ++idx) {
		for (int idx2 = 1; idx2 < MAX; ++idx2) {
			min_cost[idx][idx2] = INF;
		}
	}

	for (int idx = 0; idx < N; ++idx) {
		if (num.find(sCity[idx]) == num.end()) {
			num[sCity[idx]] = ++node_num;
		}
		if (num.find(eCity[idx]) == num.end()) {
			num[eCity[idx]] = ++node_num;
		}

		int city1 = num[sCity[idx]];
		int city2 = num[eCity[idx]];

		costs[city1].push_back({ city2, mCost[idx] });
	}

	for (int idx = 1; idx < MAX; ++idx) {
		for (int idx2 = 1; idx2 < MAX; ++idx2) {
			min_cost[idx][idx2] = INF;
		}
	}
	int cost(0), city1(0);

	for (int start = 1; start <= node_num; ++start) {
		queue<pair<int, int>>q1;
		queue<pair<int, int>>q2;
		bool flag = false;
		min_cost[start][start] = 0;
		q1.push({ 0,start });

		while (!q1.empty() || !q2.empty()) {
			if (q1.empty()) {
				cost = -q2.front().first;
				city1 = q2.front().second;
				q2.pop();
				flag = false;
			}
			else if (q2.empty()) {
				cost = -q1.front().first;
				city1 = q1.front().second;
				q1.pop();
				flag = true;
			}
			else if (q1.front().first <= q2.front().first) {
				cost = -q1.front().first;
				city1 = q1.front().second;
				q1.pop();
				flag = true;
			}
			else {
				cost = -q2.front().first;
				city1 = q2.front().second;
				q2.pop();
				flag = false;
			}

			for (int idx = 0; idx < costs[city1].size(); ++idx) {
				int city2 = costs[city1][idx].first;
				int n_cost = costs[city1][idx].second;
				if (min_cost[start][city2] > cost + n_cost) {
					min_cost[start][city2] = cost + n_cost;
					if (flag == true) {
						q1.push({ -min_cost[start][city2],city2 });
					}
					else {
						q2.push({ -min_cost[start][city2],city2 });
					}

				}
			}
		}
	}


	return node_num;
}

void add(int sCity, int eCity, int mCost) {
	int city1 = num[sCity];
	int city2 = num[eCity];

	if (min_cost[city1][city2] > mCost) {
		min_cost[city1][city2] = mCost;
		int mid = num[sCity];
		for (city1 = 1; city1 <= node_num; ++city1) {
			for (city2 = 1; city2 <= node_num; ++city2) {
				if (city1 == city2) continue;
				if (min_cost[city1][city2] > min_cost[city1][mid] + min_cost[mid][city2]) {
					min_cost[city1][city2] = min_cost[city1][mid] + min_cost[mid][city2];
				}
			}

		}

		mid = num[eCity];
		for (city1 = 1; city1 <= node_num; ++city1) {
			for (city2 = 1; city2 <= node_num; ++city2) {
				if (city1 == city2) continue;
				if (min_cost[city1][city2] > min_cost[city1][mid] + min_cost[mid][city2]) {
					min_cost[city1][city2] = min_cost[city1][mid] + min_cost[mid][city2];
				}
			}

		}
	}


	return;
}

int cost(int mHub) {

	int city2 = num[mHub];

	int sum(0);
	for (int city1 = 1; city1 <= node_num; ++city1) {
		sum += min_cost[city1][city2];
		sum += min_cost[city2][city1];
	}

	return sum;
}
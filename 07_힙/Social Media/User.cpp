#include <queue>
#define MAX 1000
#define MAX_POST 1000000
using namespace std;

bool f_lists[MAX + 1][MAX + 1];

int cur_time;

struct Post {
	int pID;
	int uID;
	int like;
	int timestamp;
};

Post posts[MAX_POST + 1];
int post_idx;

void init(int N)
{
	for (int idx = 0; idx <= MAX_POST; ++idx) {
		posts[idx].pID = 0;
		posts[idx].uID = 0;
		posts[idx].like = 0;
		posts[idx].timestamp = 0;
	}

	for (int idx = 1; idx <= MAX; ++idx) {
		for (int idx2 = 1; idx2 <= MAX; ++idx2) {
			if (idx == idx2) f_lists[idx][idx2] = 1;
			else f_lists[idx][idx2] = 0;
		}
	}
}

void follow(int uID1, int uID2, int timestamp)
{
	f_lists[uID1][uID2] = true;
}

void makePost(int uID, int pID, int timestamp)
{
	posts[pID].uID = uID;
	posts[pID].pID = pID;
	posts[pID].like = 0;
	posts[pID].timestamp = timestamp;
	post_idx = pID;
}

void like(int pID, int timestamp)
{
	++posts[pID].like;
}

struct cmp {
	bool operator()(const Post p1, const Post p2) {
		int diff_p1 = cur_time - p1.timestamp;
		int diff_p2 = cur_time - p2.timestamp;

		if (diff_p1 <= 1000 && diff_p2 <= 1000) {
			if (p1.like == p2.like) {
				return p1.timestamp < p2.timestamp;
			}
			return p1.like < p2.like;
		}
		else {
			return p1.timestamp < p2.timestamp;
		}
	}
};

void getFeed(int uID, int timestamp, int pIDList[])
{
	cur_time = timestamp;

	priority_queue<Post, vector<Post>, cmp>pq;

	int idx(0);
	bool flag(false);
	for (idx = post_idx; idx >= 0; --idx) {
		int uID2 = posts[idx].uID;
		int diff = cur_time - posts[idx].timestamp;
		if (f_lists[uID][uID2] == true) {
			pq.push({ posts[idx] });
		}
		if (diff <= 1000 && pq.size() >= 10) {
			flag = true;
		}
		if (diff > 1000 && flag == true) break;
		if (flag == false && pq.size() >= 10) {
			break;
		}
	}

	for (int idx = 0; idx < 10; ++idx) {
		pIDList[idx] = 0;
	}
	for (int idx = 0; idx < 10; ++idx) {
		if (!pq.empty()) {
			pIDList[idx] = pq.top().pID;
			pq.pop();
		}
		else break;
	}
}
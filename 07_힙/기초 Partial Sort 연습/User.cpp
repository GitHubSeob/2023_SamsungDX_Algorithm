#define MAX_SIZE 200002
int heap[MAX_SIZE][2];
int heap2[MAX_SIZE][2];
int user_idx;
int copy_idx;

void init()
{
	for (int idx = 0; idx < MAX_SIZE; ++idx) {
		heap[idx][0] = -1;
		heap[idx][1] = -1;
		heap2[idx][0] = -1;
		heap2[idx][1] = -1;
	}
	user_idx = 0;
}

void swap(int idx1, int idx2, int sheap[MAX_SIZE][2]) {
	int temp[2] = { sheap[idx1][0], sheap[idx1][1] };

	sheap[idx1][0] = sheap[idx2][0];
	sheap[idx1][1] = sheap[idx2][1];

	sheap[idx2][0] = temp[0];
	sheap[idx2][1] = temp[1];
}

void addUser(int uID, int height)
{
	++user_idx;
	heap[user_idx][0] = height;
	heap[user_idx][1] = uID;
	
	int new_user = user_idx;

	while (new_user != 1 && heap[new_user / 2][0] <= heap[new_user][0]) {
		if (heap[new_user / 2][0] == heap[new_user][0]) {
			if (heap[new_user / 2][1] > heap[new_user][1]) {
				swap(new_user, new_user / 2, heap);
			}
		}
		else if (heap[new_user / 2][0] < heap[new_user][0]) {
			swap(new_user, new_user / 2, heap);
		}
		new_user /= 2;
	}
}

void removeMax() {
	heap2[1][0] = heap2[copy_idx][0];
	heap2[1][1] = heap2[copy_idx][1];
	heap2[copy_idx][0] = -1;
	heap2[copy_idx][1] = -1;

	--copy_idx;
	int prev_idx = 0;
	int idx = 1;

	while (heap2[idx * 2][0] > -1) {

		if (heap2[idx * 2][0] > heap2[idx * 2 + 1][0]) {
			if (heap2[idx][0] < heap2[idx * 2][0]) {
				swap(idx, idx * 2, heap2);
				idx *= 2;
			}
			else if (heap2[idx][0] == heap2[idx * 2][0]) {
				if (heap2[idx][1] > heap2[idx * 2][1]) {
					swap(idx, idx * 2, heap2);
					idx *= 2;
				}
			}
		}
		else if (heap2[idx * 2][0] < heap2[idx * 2 + 1][0]) {
			if (heap2[idx][0] < heap2[idx * 2 + 1][0]) {
				swap(idx, idx * 2 + 1, heap2);
				idx = idx * 2 + 1;
			}
			else if (heap2[idx][0] == heap2[idx * 2 + 1][0]) {
				if (heap2[idx][1] > heap2[idx * 2 + 1][1]) {
					swap(idx, idx * 2 + 1, heap2);
					idx = idx * 2 + 1;
				}
			}
		}
		else if (heap2[idx * 2][0] == heap2[idx * 2 + 1][0]) {
			if (heap2[idx * 2][1] < heap2[idx * 2 + 1][1]) {
				if (heap2[idx][0] < heap2[idx * 2][0]) {
					swap(idx, idx * 2, heap2);
					idx *= 2;
				}
			}
			else if (heap2[idx * 2][1] > heap2[idx * 2 + 1][1]) {
				if (heap2[idx][0] < heap2[idx * 2 + 1][0]) {
					swap(idx, idx * 2 + 1, heap2);
					idx = idx * 2 + 1;
				}
			}
		}
		if (prev_idx == idx) break;
		prev_idx = idx;
	}
}

void copy_heap() {
	copy_idx = user_idx;
	for (int idx = 1; idx <= copy_idx; ++idx) {
		heap2[idx][0] = heap[idx][0];
		heap2[idx][1] = heap[idx][1];
	}
}

void init_res(int result[10]) {
	for (int idx = 0; idx < 10; ++idx) {
		result[idx] = 0;
	}
}

int getTop10(int result[10])
{
	copy_heap();
	init_res(result);

	int cnt(1);

	result[0] = heap2[1][1];


	for (int idx = 1; idx < 10; ++idx) {
		removeMax();
		if (heap2[1][1] == -1) break;
		++cnt;
		result[idx] = heap2[1][1];
	}

	return cnt;
}
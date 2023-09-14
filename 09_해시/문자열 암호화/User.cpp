#include <string>
using namespace std;

#define MAX 50005
#define HASH_SIZE (1<<15)
#define power_val 33

struct Node {
	int idx;
	Node* next;
	Node* prev;
};

Node node_pool[MAX];
Node Hash_T[HASH_SIZE];
int L[MAX];
int H[MAX];
string answer;
int N;

int get_A(char* str) {
	int hash = (str[0] - 'a') * power_val * power_val;
	hash = hash + (str[1] - 'a') * power_val;
	hash = hash + (str[2] - 'a');

	return hash;
}

int get_hash(int idx) {
	int hash = (answer[idx] - 'a') * power_val * power_val;
	hash = hash + (answer[idx + 1] - 'a') * power_val;
	hash = hash + (answer[idx + 2] - 'a');

	return hash;
}

int get_next(int hash, int idx) {
	hash -= (answer[idx - 1] - 'a') * power_val * power_val;
	hash *= power_val;
	hash += answer[idx + 2] - 'a';

	return hash;
}

void init(int n, char init_string[]) {
	N = n;
	answer = init_string;

	for (int idx = 0; idx < HASH_SIZE; ++idx) {
		Hash_T[idx].next = nullptr;
		Hash_T[idx].prev = nullptr;
		Hash_T[idx].idx = -1;
	}
	for (int idx = 0; idx < MAX; ++idx) {
		node_pool[idx].next = nullptr;
		node_pool[idx].prev = nullptr;
		node_pool[idx].idx = idx;
		H[idx] = 0;
	}


	H[0] = get_hash(0);
	for (int idx = 1; idx + 2 < N; ++idx) {
		H[idx] = get_next(H[idx - 1], idx);
	}
	int hash = H[N - 3];
	Hash_T[hash].next = &node_pool[N - 3];
	node_pool[N - 3].prev = &Hash_T[hash];

	for (int idx = N - 4; idx >= 0; --idx) {
		hash = H[idx];
		if (Hash_T[hash].next == nullptr) {
			Hash_T[hash].next = &node_pool[idx];
			node_pool[idx].prev = &Hash_T[hash];
		}
		else if (Hash_T[hash].next != nullptr) {
			node_pool[idx].next = Hash_T[hash].next;
			node_pool[idx].prev = &Hash_T[hash];
			Hash_T[hash].next->prev = &node_pool[idx];
			Hash_T[hash].next = &node_pool[idx];
		}
	}

	for (int idx = 1; idx + 2 < N; ++idx) {
		H[idx] = get_next(H[idx - 1], idx);
	}
}

int change(char string_A[], char string_B[]) {
	int ret(0);

	int val_A = get_A(string_A);

	Node* ptr = Hash_T[val_A].next;

	int prev_idx = -5;

	int L_cnt = 0;
	while (ptr != nullptr) {
		L[L_cnt++] = ptr->idx;
		ptr->prev->next = nullptr;
		ptr->prev = nullptr;
		ptr = ptr->next;
	}

	for (int j = 0; j < L_cnt; ++j) {
		int idx = L[j];
		if (prev_idx + 2 < idx) {
			++ret;
			prev_idx = idx;
			for (int i = idx - 2; i <= idx + 2; ++i) {
				if (i < 0) continue;
				if (i + 2 >= N) break;
				Node* pptr = node_pool[i].prev;
				if (pptr != nullptr && pptr->next != nullptr && pptr->next->next != nullptr) {
					pptr->next = pptr->next->next;
					pptr->next->prev = pptr;
				}
				else if (pptr != nullptr) {
					pptr->next = nullptr;
				}
				node_pool[i].prev = nullptr;
				node_pool[i].next = nullptr;
			}
			Node* check = Hash_T[1].next;

			answer[idx] = string_B[0];
			answer[idx + 1] = string_B[1];
			answer[idx + 2] = string_B[2];

			int val(0);
			for (int i = idx - 2; i <= idx + 2; ++i) {
				if (i < 0) continue;
				if (i + 2 >= N) break;
				if (val == 0) {
					val = get_hash(i);
				}
				else {
					val = get_next(val, i);
				}

				Node* nptr = &Hash_T[val];
				while (nptr != nullptr && nptr->next != nullptr && nptr->next->idx < i) {
					nptr = nptr->next;
				}
				if (nptr != nullptr && nptr->next == nullptr) {
					nptr->next = &node_pool[i];
					node_pool[i].prev = nptr;
					node_pool[i].next = nullptr;
				}
				else if (nptr != nullptr && nptr->next != nullptr) {
					node_pool[i].prev = nptr;
					node_pool[i].next = nptr->next;
					nptr->next->prev = &node_pool[i];
					nptr->next = &node_pool[i];
				}
			}
		}
	}

	return ret;
}

void result(char ret[]) {
	for (int idx = 0; idx < N; ++idx) {
		ret[idx] = answer[idx];
	}
}
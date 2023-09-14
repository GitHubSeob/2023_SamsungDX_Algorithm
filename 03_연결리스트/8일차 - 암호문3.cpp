#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

constexpr size_t MAX_NODE = 100000;
int node_count = 0;
Node node_pool[MAX_NODE];

Node* new_node(int data) {
	node_pool[node_count].data = data;
	node_pool[node_count].next = nullptr;

	return &node_pool[node_count++];
}

class SinglyLinkedList {
	Node head;

public:
	SinglyLinkedList() = default;
	void init() {
		node_count = 0;
		head.next = nullptr;
	}
	void insert(int loc, int val) {
		Node* node = new_node(val);
		Node* ptr = &head;
		for (int idx = 0; idx < loc; ++idx) {
			ptr = ptr->next;
		}
		node->next = ptr->next;
		ptr->next = node;

		if (loc == 0) {
			head.next = node;
		}
	}
	void remove(int loc, int cnt) {
		Node* prev_ptr = &head;

		for (int idx = 0; idx < loc; ++idx) {
			prev_ptr = prev_ptr->next;
		}

		Node* next_ptr = prev_ptr->next;
		for (int idx = 0; idx < cnt; ++idx) {
			next_ptr = next_ptr->next;
		}
		prev_ptr->next = next_ptr;
	}
	void add(int val) {
		Node* node = new_node(val);

		Node* ptr = &head;
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = node;
	}
	void print() const {
		Node* ptr = head.next;
		ptr = ptr->next;
		for (int node_idx = 0; node_idx < 10; ++node_idx) {
			cout << ptr->data << ' ';
			if (ptr->next == nullptr) break;
			ptr = ptr->next;
		}
	}
};



int main() {
	for (int test_case = 1; test_case <= 10; ++test_case) {
		int N(0), M(0);
		cin >> N;
		SinglyLinkedList slist;
		slist.init();

		for (int idx = 0; idx < N; ++idx) {
			int num(0);
			cin >> num;
			slist.insert(idx, num);
		}

		cin >> M;
		for (int idx = 0; idx < M; ++idx) {
			char cmd;
			int loc(0), cnt(0), num(0);
			cin >> cmd;
			switch (cmd) {
			case 'I':
				cin >> loc >> cnt;
				for (int idx2 = 0; idx2 < cnt; ++idx2) {
					cin >> num;
					slist.insert(loc + 1, num);
					++loc;
				}
				break;
			case 'D':
				cin >> loc >> cnt;
				slist.remove(loc + 1, cnt);
				break;
			case 'A':
				cin >> cnt;
				for (int idx2 = 0; idx2 < cnt; ++idx2) {
					cin >> num;
					slist.add(num);
				}
				break;

			default:
				break;
			}
		}
		cout << "#" << test_case << ' ';
		slist.print();
		cout << '\n';
	}
}
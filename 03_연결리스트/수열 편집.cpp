#include <iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

constexpr size_t MAX_NODE = 10000;
int node_count = 0;
Node node_pool[MAX_NODE];

Node* new_node(int val) {	
	node_pool[node_count].data = val;
	node_pool[node_count].next = nullptr;

	return &node_pool[node_count++];
}

class SinglyLinkedList {
	Node head;
public:
	SinglyLinkedList() = default;
	void init() {
		head.next = nullptr;
		node_count = 0;
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
	void remove(int loc) {
		Node* prev_ptr = &head;

		for (int idx = 0; idx < loc; ++idx) {
			prev_ptr = prev_ptr->next;
		}
		prev_ptr->next = prev_ptr->next->next;
	}

	void change(int loc, int val) {
		Node* ptr = head.next;
		for (int idx = 0; idx < loc; ++idx) {				
			ptr = ptr->next;
		}
		ptr->data = val;
	}

	void find(int loc)const {
		Node* ptr = head.next;
		for (int idx = 0; idx < loc; ++idx) {
			if (ptr->next == nullptr) {
				cout << "-1\n";
				return;
			}
			ptr = ptr->next;
		}

		cout << ptr->data << '\n';
	}
};

int main() {
	int T(0);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N(0), M(0), L(0);
		cin >> N >> M >> L;
		SinglyLinkedList slist;
		slist.init();
		for (int idx = 0; idx < N; ++idx) {
			int value;
			cin >> value;
			slist.insert(idx, value);
		}
		for (int idx = 0; idx < M; ++idx) {
			char cmd(' ');
			int loc(0), value(0);
			cin >> cmd;
			switch (cmd) {
			case 'I':
				cin >> loc >> value;
				slist.insert(loc, value);
				break;

			case 'D':
				cin >> loc;
				slist.remove(loc);
				break;

			case 'C':
				cin >> loc >> value;
				slist.change(loc, value);
				break;

			default:
				break;
			}
		}
		cout << "#" << test_case << " ";
		slist.find(L);
	}
}
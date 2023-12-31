﻿#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
};

constexpr size_t MAX_NODE = 10000;
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
	void insert(int x) {
		Node *node = new_node(x);
		if (node_count != 1)
			node->next = head.next;		
		head.next = node;
	}
	void remove(int x) {
		Node* prev_ptr= &head;
		while (prev_ptr->next != nullptr && prev_ptr->next->data != x) {
			prev_ptr = prev_ptr->next;
		}
		if (prev_ptr->next != nullptr) {
			prev_ptr->next = prev_ptr->next->next;
		}
	}
	bool find(int x) const {
		Node *ptr = head.next;
		while (ptr != nullptr && ptr->data != x) {
			ptr = ptr->next;
		}
		return ptr != nullptr;
	}
	void print()const {
		Node* ptr = head.next;		
		cout << "[List]";
		while (ptr != nullptr) {
			cout << ptr->data<< " ";
			if (ptr->next != nullptr) {
				cout << "-> ";
			}
			ptr = ptr->next;
		}
		cout << '\n';
	}
};

int main() {
	SinglyLinkedList slist;
	int a(0), b(0);
	while (1) {
		cin >> a;
		switch (a) {
		case 0:
			slist.init();
			slist.print();
			break;

		case 1:
			cin >> b;
			slist.insert(b);
			slist.print();
			break;
		case 2:
			cin >> b;
			slist.remove(b);
			slist.print();
			break;
		case 3:
			cin >> b;
			slist.find(b) ? cout << "found" : cout << "not found";
			cout << '\n';
			break;
		default:
			cout << "wrong input\n";
			return 0;
		}
	}
}
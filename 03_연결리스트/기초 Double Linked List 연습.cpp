#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, FIND, REMOVE, PRINT, PRINT_REVERSE, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD: // 1
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL: // 2
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM: // 3
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case FIND: // 4
			scanf("%d", &data);
			num = findNode(data);
			printf("%d\n", num);
			break;
		case REMOVE: // 5
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT: // 6
			cnt = getList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case PRINT_REVERSE: // 7
			cnt = getReversedList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
}

int main(void) {
	//setbuf(stdout, NULL);
	//freopen("dll_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}

#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	head = nullptr;
}

void addNode2Head(int data)
{
	Node* new_node = getNode(data);
	if (head == nullptr) {
		head = new_node;
		return;
	}

	new_node->next = head;
	head->prev = new_node;
	head = new_node;
}

void addNode2Tail(int data)
{
	Node* new_node = getNode(data);
	Node* ptr = head;
	if (head == nullptr) {
		head = new_node;
		return;
	}
	while (ptr->next != nullptr) {
		ptr = ptr->next;
	}

	new_node->prev = ptr;
	ptr->next = new_node;
}

void addNode2Num(int data, int num)
{
	Node* new_node = getNode(data);
	Node* prev_ptr = head;
	if (num == 1) {
		new_node->next = head;
		head->prev = new_node;
		head = new_node;		
		return;
	}

	for (int idx = 2; idx < num; ++idx) {
		prev_ptr = prev_ptr->next;
	}

	if (prev_ptr->next != nullptr) {
		new_node->next = prev_ptr->next;
		prev_ptr->next->prev = new_node;
	}
	new_node->prev = prev_ptr;
	prev_ptr->next = new_node;
}

int findNode(int data)
{
	int node_cnt(0);
	Node* ptr = head;
	while (ptr->data != data) {
		++node_cnt;
		ptr = ptr->next;
	}
	return node_cnt + 1;
}

void removeNode(int data)
{
	Node* prev_ptr = head;	
	if (head->data == data) {
		head = head->next;
		head->prev = nullptr;
		return;
	}
	while (prev_ptr->next != nullptr && prev_ptr->next->data != data) {
		prev_ptr = prev_ptr->next;
	}
	if (prev_ptr->next != nullptr&& prev_ptr->next->data==data) {
		prev_ptr->next = prev_ptr->next->next;
		if (prev_ptr->next != nullptr)
			prev_ptr->next->prev = prev_ptr;
	}
	
}

int getList(int output[MAX_NODE])
{
	Node* ptr = head;
	int node_cnt(0);
	while (ptr != nullptr) {
		output[node_cnt] = ptr->data;
		++node_cnt;
		ptr = ptr->next;
	}
	return node_cnt;
}

int getReversedList(int output[MAX_NODE])
{
	Node* ptr = head;
	int node_cnt(0);
	while (ptr->next != nullptr) {
		ptr = ptr->next;
	}
	while (ptr != nullptr) {
		output[node_cnt] = ptr->data;
		ptr = ptr->prev;
		++node_cnt;
	}
	return node_cnt;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, REMOVE, PRINT, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD:
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL:
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM:
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case REMOVE:
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT:
			cnt = getList(output);
			i = 0;
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
	//freopen("sll_input.txt", "r", stdin);

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
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
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
	new_node->next = head;
	head = new_node;
}

void addNode2Tail(int data)
{
	Node* ptr = head;
	Node* new_node = getNode(data);
	if (head == nullptr) {
		new_node->next = head;
		head = new_node;
	}
	else {
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = new_node;
	}

}

void addNode2Num(int data, int num)
{
	Node* ptr = head;
	Node* new_node = getNode(data);
	if (num == 1) {
		new_node->next = head;
		head = new_node;
	}
	else {
		for (int idx = 2; idx < num; ++idx) {
			ptr = ptr->next;
		}
		new_node->next = ptr->next;
		ptr->next = new_node;
	}
}

void removeNode(int data)
{
	Node* prev_ptr = head;
	if (head->data == data) {
		head = head->next;
		return;
	}
	while (prev_ptr->next != nullptr && prev_ptr->next->data != data) {
		prev_ptr = prev_ptr->next;
	}
	if (prev_ptr->next != nullptr) {
		prev_ptr->next = prev_ptr->next->next;
	}
}

int getList(int output[MAX_NODE])
{
	int output_node_cnt(0);
	Node* ptr = head;
	while (ptr != nullptr) {
		output[output_node_cnt] = ptr->data;
		++output_node_cnt;
		ptr = ptr->next;
	}
	return output_node_cnt;
}
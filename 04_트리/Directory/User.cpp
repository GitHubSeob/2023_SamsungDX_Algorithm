#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_NODE 50001
#include <string>
using namespace std;

struct Node {
	Node* parent;
	Node* child;
	Node* next;
	string name;
};

Node* root;
Node node_pool[MAX_NODE];
int node_count;

Node* new_node(string name) {
	node_pool[node_count].parent = nullptr;
	node_pool[node_count].child = nullptr;
	node_pool[node_count].next = nullptr;
	node_pool[node_count].name = name;

	return &node_pool[node_count++];
}


void init(int n) {
	for (int idx = 0; idx < n; ++idx) {
		node_pool[idx].parent = nullptr;
		node_pool[idx].child = nullptr;
		node_pool[idx].next = nullptr;
		node_pool[idx].name.clear();
	}
	node_count = 0;
	root = new_node("/");
}

Node* find_loc(char path[PATH_MAXLEN + 1]) {
	Node* ptr = root;
	string p = path;
	string dir("");
	for (int idx = 1; idx < p.size(); ++idx) {
		if (p[idx] == '/') {
			if (ptr->child != nullptr) {
				ptr = ptr->child;
			}
			while (ptr->next != nullptr && ptr->name != dir) {
				ptr = ptr->next;
			}
			dir.clear();
		}
		else {
			dir += p[idx];
		}
	}
	return ptr;
}

void add(Node* ptr, Node* dptr) {
	if (dptr->child == nullptr) {
		ptr->parent = dptr;
		dptr->child = ptr;
	}
	else if (dptr->child != nullptr) {
		ptr->parent = dptr;
		dptr = dptr->child;
		while (dptr->next != nullptr) {
			dptr = dptr->next;
		}
		dptr->next = ptr;
	}
}

void rem(Node* node) {
	if (node->parent->child == node) {
		if (node->next == nullptr) {
			node->parent->child = nullptr;
			node->parent = nullptr;
		}
		else if (node->next != nullptr) {
			node->parent->child = node->next;
			node->next = nullptr;
			node->parent = nullptr;
		}
	}
	else if (node->parent->child != node) {
		Node* prev = node->parent->child;
		while (prev->next != node) {
			prev = prev->next;
		}
		if (node->next == nullptr) {
			prev->next = nullptr;
		}
		else if (node->next != nullptr) {
			prev->next = node->next;
			node->next = nullptr;
		}
		node->parent = nullptr;
	}
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* ptr = find_loc(path);
	Node* node = new_node(name);

	add(node, ptr);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* ptr = find_loc(path);
	rem(ptr);
}

void cp(Node* sptr, Node* dptr) {
	Node* node = new_node(sptr->name);

	add(node, dptr);

	if (sptr->child != nullptr) {
		cp(sptr->child, node);
	}
	if (sptr->next != nullptr) {
		cp(sptr->next, dptr);
	}

}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* sptr = find_loc(srcPath);
	Node* dptr = find_loc(dstPath);

	Node* node = new_node(sptr->name);
	add(node, dptr);

	if (sptr->child != nullptr)
		cp(sptr->child, node);
}


void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* sptr = find_loc(srcPath);
	Node* dptr = find_loc(dstPath);
	rem(sptr);
	add(sptr, dptr);
}

int DFS(Node* ptr) {
	int cnt(1);
	if (ptr == nullptr) {
		return 0;
	}
	if (ptr->next != nullptr) {
		cnt += DFS(ptr->next);
	}
	if (ptr->child != nullptr) {
		cnt += DFS(ptr->child);
	}
	return cnt;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	int cnt(0);
	Node* ptr = find_loc(path);
	if (ptr->child != nullptr)
		cnt = DFS(ptr->child);

	return cnt;
}
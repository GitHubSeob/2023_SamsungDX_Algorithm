#include <string>
#include <cstring>
#define MAX 50001
#define MOD 200003
#define power_val 33;
#define HASH_SIZE 200003

using namespace std;

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

struct Node {
	struct Sub* name;
	struct Sub* num;
	struct Sub* bday;
	struct Sub* mail;
	struct Sub* memo;
};

struct Sub { // name, num, bday, mail, memo
	int idx;
	string str;
	Sub* prev;
	Sub* next;
	struct Hash* H_prev;
	struct Node* parent;
};

struct Hash {
	struct Sub* next;
};

Node user[MAX];
Sub info[MAX * 5];
Hash hash_T[HASH_SIZE];
int user_cnt, info_cnt;

Node* new_node(int idx) {
	user[user_cnt].name = nullptr;
	user[user_cnt].num = nullptr;
	user[user_cnt].bday = nullptr;
	user[user_cnt].mail = nullptr;
	user[user_cnt].memo = nullptr;

	return &user[user_cnt++];
}

Sub* new_sub(string data) {
	info[info_cnt].idx = 0;
	info[info_cnt].str = data;
	info[info_cnt].parent = nullptr;
	info[info_cnt].prev = nullptr;
	info[info_cnt].next = nullptr;
	info[info_cnt].H_prev = nullptr;

	return &info[info_cnt++];
}

void InitDB()
{
	for (int idx = 0; idx < HASH_SIZE; ++idx) {
		hash_T[idx].next = nullptr;
	}
	info_cnt = 0;
	user_cnt = 0;
}

void link(Sub* sub, string str) {
	int val(0), power(1);
	for (int idx = 0; idx < str.size(); ++idx) {
		val += str[idx] * power % MOD;
		val %= MOD;
		if (idx + 1 < str.size()) {
			power *= power_val;
			power %= MOD;
		}
	}
	Hash* H = &hash_T[val];
	if (H->next == nullptr) {
		H->next = sub;
		sub->H_prev = H;
		sub->next = nullptr;
		sub->prev = nullptr;
	}
	else if (H->next != nullptr) {
		sub->next = H->next;
		sub->next->prev = sub;
		sub->next->H_prev = nullptr;
		H->next = sub;
		sub->H_prev = H;
		sub->prev = nullptr;
	}
}

int get_hash(string str) {
	int val(0), power(1);
	for (int idx = 0; idx < str.size(); ++idx) {
		val += str[idx] * power % MOD;
		val %= MOD;
		if (idx + 1 < str.size()) {
			power *= power_val;
			power %= MOD;
		}
	}
	return val;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	Node* node = new_node(user_cnt);

	Sub* n_name = new_sub(name);
	n_name->parent = node;
	n_name->idx = 0;
	node->name = n_name;
	link(n_name, name);

	Sub* n_num = new_sub(number);
	n_num->parent = node;
	n_num->idx = 1;
	node->num = n_num;
	link(n_num, number);

	Sub* n_bday = new_sub(birthday);
	n_bday->parent = node;
	n_bday->idx = 2;
	node->bday = n_bday;
	link(n_bday, birthday);

	Sub* n_mail = new_sub(email);
	n_mail->parent = node;
	n_mail->idx = 3;
	node->mail = n_mail;
	link(n_mail, email);

	Sub* n_memo = new_sub(memo);
	n_memo->parent = node;
	n_memo->idx = 4;
	node->memo = n_memo;
	link(n_memo, memo);
}

void rem(Sub* sub) {
	if (sub->next == nullptr) {
		if (sub->prev == nullptr) {
			sub->H_prev->next = nullptr;
			sub->H_prev = nullptr;
		}
		else if (sub->prev != nullptr) {
			sub->prev->next = nullptr;
		}
	}
	else if (sub->next != nullptr) {
		if (sub->prev == nullptr) {
			sub->H_prev->next = sub->next;
			sub->next->prev = nullptr;
			sub->next->H_prev = sub->H_prev;
		}
		else if (sub->prev != nullptr) {
			sub->prev->next = sub->next;
			sub->next->prev = sub->prev;
		}
	}
}

int Delete(FIELD field, char* str)
{
	int del_cnt(0);
	int val(get_hash(str));

	Sub* sptr = hash_T[val].next;
	Node* ptr = nullptr;

	while (sptr != nullptr) {
		if (sptr->idx == field && sptr->str == str) {
			++del_cnt;
			ptr = sptr->parent;
			rem(ptr->name);
			rem(ptr->num);
			rem(ptr->bday);
			rem(ptr->mail);
			rem(ptr->memo);
		}
		sptr = sptr->next;
	}
	return del_cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int change_cnt(0);
	int val(get_hash(str));
	int c_val(get_hash(changestr));

	Sub* sptr = hash_T[val].next;
	Node* ptr = nullptr;
	Sub* pptr = nullptr;

	while (sptr != nullptr) {
		pptr = sptr->next;
		if (sptr->idx == field && sptr->str == str) {
			++change_cnt;
			ptr = sptr->parent;
			if (changefield == 0) {
				rem(ptr->name);
				link(ptr->name, changestr);
				ptr->name->str = changestr;
			}
			else if (changefield == 1) {
				rem(ptr->num);
				link(ptr->num, changestr);
				ptr->num->str = changestr;
			}
			else if (changefield == 2) {
				rem(ptr->bday);
				link(ptr->bday, changestr);
				ptr->bday->str = changestr;
			}
			else if (changefield == 3) {
				rem(ptr->mail);
				link(ptr->mail, changestr);
				ptr->mail->str = changestr;
			}
			else if (changefield == 4) {
				rem(ptr->memo);
				link(ptr->memo, changestr);
				ptr->memo->str = changestr;
			}
		}
		if (sptr == pptr) break;
		sptr = pptr;
	}

	return change_cnt;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{

	RESULT result;
	result.count = 0;

	int str_cnt(0);
	int val = get_hash(str);
	Sub* sptr = hash_T[val].next;

	while (sptr != nullptr) {
		if (sptr->idx == field && sptr->str == str) {
			++result.count;
			if (result.count == 1) {
				Node* rptr = sptr->parent;
				if (ret_field == 0) {
					strcpy(result.str, rptr->name->str.c_str());

					str_cnt = rptr->name->str.size();
				}
				else if (ret_field == 1) {
					strcpy(result.str, rptr->num->str.c_str());
					str_cnt = rptr->num->str.size();
				}
				else if (ret_field == 2) {
					strcpy(result.str, rptr->bday->str.c_str());

					str_cnt = rptr->bday->str.size();
				}
				else if (ret_field == 3) {
					strcpy(result.str, rptr->mail->str.c_str());

					str_cnt = rptr->mail->str.size();
				}
				else if (ret_field == 4) {
					strcpy(result.str, rptr->memo->str.c_str());

					str_cnt = rptr->memo->str.size();
				}
			}
			else {
				str_cnt = 0;
			}
		}
		sptr = sptr->next;
	}


	return result;
}
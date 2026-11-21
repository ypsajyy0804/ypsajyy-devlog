#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表上节点的结构
typedef struct Node {
	char *key;	//节点名
	int val;	//节点值
	struct Node *next;	//自引用
} Node;

//哈希表的结构
typedef struct {
	Node **buckets;		//二级指针，可看做指针数组，指向存放 Node* 的数组
	unsigned bucket_count;	//‘桶’ 的数量，可看做数组的可存放元素
	unsigned size;		//整个哈希表中存放的键值对数
} HT;

//创建拥有 bucket_count 个存储桶/格子的哈希表
HT *ht_create(unsigned bucket_count){
	if(bucket_count == 0) return NULL;

	HT *ht = malloc(sizeof(HT));	//定义指向哈希表的指针并分配空间

	if(ht == NULL){
		return NULL;
	}

	ht->buckets = calloc(bucket_count, sizeof(Node*)); //为二级指针分配空间，可看做申请存放 Node* 数组的空间

	if(!(ht->buckets)) {
		free(ht);

		return NULL;
	}

	ht->bucket_count = bucket_count;

	ht->size = 0;

	return ht;
}

void ht_free(HT *h){
	if(h == NULL) return;

	for(int i = 0; i < (int)(h->bucket_count); i++) {
		Node *cur = h->buckets[i];
		while(cur != NULL) {
			free(cur->key);

			Node *temp = cur;
			cur = cur->next;
			free(temp);
		}
	}

	free(h->buckets);
	free(h);
}

//往哈希表中新增键值对
int ht_put(HT *h, const char *key, int val){
	//定义哈希函数：key 各个字符 ASCII 码相加，计算出哈希值
	int sum = 0;
	for(const char *p = key; *p != '\0'; ++p) {
		sum += *p;
	}

	unsigned num = sum % h->bucket_count;	//哈希值

	int found = 0;	//用于判断哈希表中是否存在传入的 key

	Node *cur = h->buckets[num];	//保存当前节点

	while(cur != NULL){
		if(strcmp(key, cur->key) == 0) {
			found = 1;
			break;
		}

		//在非空链表的情况下，循环内不允许使 cur 循环至 NULL，cur 最总为最后一个有值的 Node
		if(cur->next == NULL) break;

		cur = cur->next;
	}

	//如果哈希表中存在该 key，只修改节点值
	if(found){
		cur->val = val;
		return 0;
	}

	//为新节点分配空间
	Node *newnode = malloc(sizeof(Node));

	if(newnode == NULL) return -1;

	newnode->key = strdup(key);	//利用 strdup 复制一份副本并返回指针
	
	if(newnode->key == NULL) {
		perror("strdup");
		exit(1);
	}

	newnode->val = val;
	newnode->next = NULL;

	//对于空链表的情况，新节点做为头节点，桶/格子里直接存新节点的地址
	if(cur == NULL) h->buckets[num] = newnode;

	//非空链表的情况，将新节点接到链表末尾
	if(cur != NULL) cur->next = newnode;

	//新增键值对 size 值加一
	h->size++;

	return 1;
}

int ht_get(const HT *h, const char *key, int *out){
	//哈希函数用 key 计算哈希值
	int sum = 0;
	for(const char *p = key; *p != '\0'; p++) {
		sum += *p;
	}

	unsigned num = sum % h->bucket_count;	//计算目标键值对所在的格子/桶

	Node *cur = h->buckets[num];	//保存当前节点

	//遍历链表寻找 key
	while(cur != NULL) {
		if(strcmp(key, cur->key) == 0) {
			*out = cur->val;
			return 1;
		}

		cur = cur->next;
	}

	return 0;
}

unsigned ht_count(const HT *h){
	return h->size;
}

int ht_del(HT *h, const char *key) {
	int sum = 0;
	for(const char *p = key; *p != '\0'; p++) {
		sum += *p;
	}

	unsigned num = sum % h->bucket_count;

	Node *head = h->buckets[num];

	if(head == NULL) return 0;

	if(strcmp(key, head->key) == 0) {
		h->buckets[num] = head->next;

		Node *temp = head;

		head = h->buckets[num];

		free(temp->key);
		free(temp);

		h->size--;

		return 1;
	}

	Node *prev = head;

	Node *cur = prev->next;

	while(cur != NULL) {
		if(strcmp(key, cur->key) == 0) {
			prev->next = cur->next;

			free(cur->key);
			free(cur);

			h->size--;

			return 1;
		}
		prev = cur;
		cur = prev->next;
	}
	return 0;
}

int main() {
	HT *h = ht_create(8);

	ht_put(h, "one", 1);
	ht_put(h, "two",2);
	ht_put(h, "three",3);
	ht_put(h, "four",4);
	ht_put(h, "five",5);
	ht_put(h, "six",6);
	ht_put(h, "seven",7);
	ht_put(h, "eight",8);
	ht_put(h, "nine",9);
	ht_put(h, "ten",10);

	int out;

	const char *k[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
	int want[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int count = 0;

	for(int i = 0; i < 10; i++) {
		if(ht_get(h, k[i], &out) == 1 && out == want[i]) count++;
	}

	printf("%d/10 ok\n", count);

	if(ht_get(h, "eleven", &out) == 0) printf("eleven: not found\n");

	printf("put three again = %d\n", ht_put(h, "three", 99));

	ht_get(h, "three", &out);
	printf("three = %d, count = %u\n", out, ht_count(h));

	printf("del one = %d\n", ht_del(h, "one"));
	printf("del one again = %d\n", ht_del(h, "one"));
	printf("del nope = %d\n", ht_del(h, "nope"));
	printf("count = %u\n", ht_count(h));

	/* 把剩下的全删掉 */
	const char *rest[9] = {"two","three","four","five","six","seven","eight","nine","ten"};
	for (int i = 0; i < 9; i++) ht_del(h, rest[i]);
	printf("after delete all: count = %u\n", ht_count(h));

	printf("del one after empty = %d\n", ht_del(h, "one"));

	ht_free(h);

	return 0;
}

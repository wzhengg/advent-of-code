#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;
typedef struct Node Node;

struct List {
	Node *head;
	Node *tail;
};

struct Node {
	uint64_t size;
	Node *parent;
	Node *next;
	List subdirs;
};

uint64_t solve(Node *root, uint64_t *sum) {
	uint64_t size = root->size;
	for (Node *dir = root->subdirs.head; dir; dir = dir->next)
		size += solve(dir, sum);

	if (size <= 100000)
		*sum += size;

	return size;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	Node *root = NULL;
	Node *curr = root;

	char line[32];
	while (fgets(line, sizeof(line), fp)) {
		if (!strcmp(line, "$ ls\n") || !strncmp(line, "dir", 3))
			continue;

		uint64_t size;
		if (sscanf(line, "%lu", &size) == 1) {
			curr->size += size;
			continue;
		}

		char dirname[32];
		assert(sscanf(line, "$ cd %s", dirname) == 1);

		if (!strcmp(dirname, "..")) {
			curr = curr->parent;
			continue;
		}

		Node *dir = malloc(sizeof(Node));
		if (!dir) exit(1);
		dir->parent = curr;
		dir->next = NULL;
		dir->size = 0;
		dir->subdirs.head = NULL;
		dir->subdirs.tail = NULL;

		if (!root) {
			root = curr = dir;
			continue;
		}

		if (!curr->subdirs.head) {
			curr->subdirs.head = curr->subdirs.tail = dir;
		} else {
			curr->subdirs.tail->next = dir;
			curr->subdirs.tail = dir;
		}

		curr = dir;
	}

	uint64_t res = 0;
	solve(root, &res);
	printf("%lu\n", res);

	return 0;
}

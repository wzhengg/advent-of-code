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
	int64_t size;
	Node *parent;
	Node *next;
	List subdirs;
};

int64_t totalsize(Node *root) {
	for (Node *dir = root->subdirs.head; dir; dir = dir->next)
		root->size += totalsize(dir);
	return root->size;
}

int64_t solve(Node *root, int64_t min) {
	if (root->size < min)
		return -1;

	int64_t best = root->size;
	for (Node *dir = root->subdirs.head; dir; dir = dir->next) {
		int64_t res = solve(dir, min);
		if (res != -1 && res < best)
			best = res;
	}

	return best;
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

		int64_t size;
		if (sscanf(line, "%ld", &size) == 1) {
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

	int64_t free = 70000000 - totalsize(root);
	int64_t res = solve(root, 30000000 - free);
	printf("%ld\n", res);

	return 0;
}

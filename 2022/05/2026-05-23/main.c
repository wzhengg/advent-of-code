#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define STACKS 9
#define STACKLINES 8

typedef struct Node Node;
struct Node {
	Node *next;
	char c;
};

Node *reverse(Node *head) {
	Node *prev = NULL;
	Node *curr = head;

	while (curr) {
		Node *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	char buf[40];
	Node *stacks[STACKS] = {0};

	for (int i = 0; i < STACKLINES; ++i) {
		assert(fgets(buf, sizeof(buf), fp));

		for (int j = 0; j < STACKS; ++j) {
			char c = buf[4*j+1];
			if ('A' <= c && c <= 'Z') {
				Node *node = malloc(sizeof(Node));
				assert(node);
				node->c = c;

				node->next = stacks[j];
				stacks[j] = node;
			}
		}
	}

	assert(fgets(buf, sizeof(buf), fp));
	assert(fgets(buf, sizeof(buf), fp));

	for (int i = 0; i < STACKS; ++i)
		stacks[i] = reverse(stacks[i]);

	while (fgets(buf, sizeof(buf), fp)) {
		int qty, src, dst;
		assert(sscanf(buf, "move %d from %d to %d", &qty, &src, &dst) == 3);

		--src;
		--dst;

		Node *head = stacks[src];
		Node *tail = head;
		for (int i = 0; i < qty-1; ++i)
			tail = tail->next;
		stacks[src] = tail->next;
		tail->next = stacks[dst];
		stacks[dst] = head;
	}

	char res[STACKS+1];
	for (int i = 0; i < STACKS; ++i)
		res[i] = stacks[i]->c;
	res[STACKS] = 0;

	printf("%s", res);

	return 0;
}

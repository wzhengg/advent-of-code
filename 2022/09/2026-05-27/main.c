#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define P 10
#define SETCAP (1<<P)

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct Position Position;
struct Position {
	int32_t x;
	int32_t y;
};

typedef struct Node Node;
struct Node {
	uint64_t key;
	Node *next;
};

typedef struct HashSet HashSet;
struct HashSet {
	Node *arr[SETCAP];
	int size;
};

void setadd(HashSet *set, Position pos) {
	uint64_t key = ((uint64_t)pos.x << 32) | (uint32_t)pos.y;
	int hash = (key * 0x9e3779b97f4a7c15ull) >> (64 - P);

	for (Node *n = set->arr[hash]; n; n = n->next)
		if (n->key == key)
			return;

	Node *node = malloc(sizeof(Node));
	if (!node) exit(1);

	node->key = key;
	node->next = set->arr[hash];
	set->arr[hash] = node;
	set->size++;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	Position head = {0};
	Position tail = {0};

	HashSet set = {0};
	setadd(&set, tail);

	char buf[8];
	while (fgets(buf, sizeof(buf), fp)) {
		char dir;
		int count;
		assert(sscanf(buf, "%c %d", &dir, &count) == 2);

		for (int i = 0; i < count; ++i) {
			switch (dir) {
				case 'U': ++head.y; break;
				case 'D': --head.y; break;
				case 'L': --head.x; break;
				case 'R': ++head.x; break;
				default: assert(0);
			}

			if (ABS(head.x-tail.x) > 1 || ABS(head.y-tail.y) > 1) {
				if (head.x == tail.x && tail.y < head.y) {
					++tail.y;
				} else if (head.x == tail.x && tail.y > head.y) {
					--tail.y;
				} else if (head.y == tail.y && tail.x < head.x) {
					++tail.x;
				} else if (head.y == tail.y && tail.x > head.x) {
					--tail.x;
				} else if ((tail.x-head.x == 2 && tail.y-head.y == -1) || (tail.x-head.x == 1 && tail.y-head.y == -2)) {
					--tail.x; ++tail.y;
				} else if ((tail.x-head.x == -1 && tail.y-head.y == -2) || (tail.x-head.x == -2 && tail.y-head.y == -1)) {
					++tail.x; ++tail.y;
				} else if ((tail.x-head.x == -2 && tail.y-head.y == 1) || (tail.x-head.x == -1 && tail.y-head.y == 2)) {
					++tail.x; --tail.y;
				} else if ((tail.x-head.x == 1 && tail.y-head.y == 2) || (tail.x-head.x == 2 && tail.y-head.y == 1)) {
					--tail.x; --tail.y;
				} else {
					assert(0);
				}
				setadd(&set, tail);
			}
		}
	}

	printf("%d\n", set.size);

	return 0;
}

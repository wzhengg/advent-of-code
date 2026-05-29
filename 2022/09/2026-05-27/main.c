#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define KNOTS 10

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

	for (Node *node = set->arr[hash]; node; node = node->next)
		if (node->key == key)
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

	Position ps[KNOTS] = {0};
	Position *head = ps;
	Position *tail = &ps[KNOTS-1];

	HashSet set = {0};
	setadd(&set, *tail);

	char buf[8];
	while (fgets(buf, sizeof(buf), fp)) {
		char dir;
		int count;
		assert(sscanf(buf, "%c %d", &dir, &count) == 2);

		for (int i = 0; i < count; ++i) {
			switch (dir) {
				case 'U': head->y++; break;
				case 'D': head->y--; break;
				case 'L': head->x--; break;
				case 'R': head->x++; break;
				default: assert(0);
			}

			for (int j = 1; j < KNOTS; ++j) {
				Position *p1 = &ps[j-1];
				Position *p2 = &ps[j];

				int32_t x1 = p1->x;
				int32_t y1 = p1->y;
				int32_t x2 = p2->x;
				int32_t y2 = p2->y;

				if (ABS(x1-x2) <= 1 && ABS(y1-y2) <= 1)
					break;

				if (x1 == x2 && y2 < y1) {
					p2->y++;
				} else if (x1 == x2 && y2 > y1) {
					p2->y--;
				} else if (y1 == y2 && x2 < x1) {
					p2->x++;
				} else if (y1 == y2 && x2 > x1) {
					p2->x--;
				} else if ((x2-x1 == 2 && y2-y1 == -2) || (x2-x1 == 2 && y2-y1 == -1) || (x2-x1 == 1 && y2-y1 == -2)) {
					p2->x--; p2->y++;
				} else if ((x2-x1 == -2 && y2-y1 == -2) || (x2-x1 == -1 && y2-y1 == -2) || (x2-x1 == -2 && y2-y1 == -1)) {
					p2->x++; p2->y++;
				} else if ((x2-x1 == -2 && y2-y1 == 2) || (x2-x1 == -2 && y2-y1 == 1) || (x2-x1 == -1 && y2-y1 == 2)) {
					p2->x++; p2->y--;
				} else if ((x2-x1 == 2 && y2-y1 == 2) || (x2-x1 == 1 && y2-y1 == 2) || (x2-x1 == 2 && y2-y1 == 1)) {
					p2->x--; p2->y--;
				} else {
					assert(0);
				}

				if (p2 == tail)
					setadd(&set, *tail);
			}
		}
	}

	printf("%d\n", set.size);

	return 0;
}

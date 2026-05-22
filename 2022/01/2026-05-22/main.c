#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELVES 300

int cmp(const void *p1, const void *p2) {
	long a = *(long *)p1;
	long b = *(long *)p2;

	if (a < b) {
		return 1;
	} else if (a > b) {
		return -1;
	} else {
		return 0;
	}
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		exit(1);
	}

	long cals[MAX_ELVES] = {0};
	int n = 0;
	long cur = 0;

	char buf[8];
	while (fgets(buf, sizeof(buf), fp)) {
		long val = strtol(buf, NULL, 10);
		if (val) {
			cur += val;
		} else {
			assert(n < MAX_ELVES);
			cals[n++] = cur;
			cur = 0;
		}
	}

	assert(n >= 3);
	qsort(cals, n, sizeof(cals[0]), cmp);

	printf("%ld\n", cals[0]+cals[1]+cals[2]);

	return 0;
}

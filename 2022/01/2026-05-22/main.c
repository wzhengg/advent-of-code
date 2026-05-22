#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		exit(1);
	}

	long max = 0;
	long cur = 0;

	char buf[8];
	while (fgets(buf, sizeof(buf), fp)) {
		long cals = strtol(buf, NULL, 10);
		if (cals) {
			cur += cals;
			continue;
		}

		if (cur > max) {
			max = cur;
		}
		cur = 0;
	}

	printf("%ld\n", max);

	return 0;
}

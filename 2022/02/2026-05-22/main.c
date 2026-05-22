#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		exit(1);
	}

	long res = 0;

	char buf[5];
	while (fgets(buf, sizeof(buf), fp)) {
		char a, b;
		assert(sscanf(buf, "%c %c", &a, &b) == 2);

		if (a == 'A') {
			if (b == 'X') res += 3;
			else if (b == 'Y') res += 4;
			else if (b == 'Z') res += 8;
			else assert(0);
		} else if (a == 'B') {
			if (b == 'X') res += 1;
			else if (b == 'Y') res += 5;
			else if (b == 'Z') res += 9;
			else assert(0);
		} else if (a == 'C') {
			if (b == 'X') res += 2;
			else if (b == 'Y') res += 6;
			else if (b == 'Z') res += 7;
			else assert(0);
		} else {
			assert(0);
		}
	}

	printf("%ld\n", res);

	return 0;
}

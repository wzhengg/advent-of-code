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

		if (b == 'X') {
			res += 1;
			if (a == 'A') res += 3;
			else if (a == 'B') ;
			else if (a == 'C') res += 6;
			else assert(0);
		} else if (b == 'Y') {
			res += 2;
			if (a == 'A') res += 6;
			else if (a == 'B') res += 3;
			else if (a == 'C') ;
			else assert(0);
		} else if (b == 'Z') {
			res += 3;
			if (a == 'A') ;
			else if (a == 'B') res += 6;
			else if (a == 'C') res += 3;
			else assert(0);
		} else {
			assert(0);
		}
	}

	printf("%ld\n", res);

	return 0;
}

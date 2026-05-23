#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	int res = 0;

	char buf[16];
	while (fgets(buf, sizeof(buf), fp)) {
		int start1, end1, start2, end2;
		assert(sscanf(buf, "%d-%d,%d-%d", &start1, &end1, &start2, &end2) == 4);
		if ((start1 >= start2 && end1 <= end2) || (start2 >= start1 && end2 <= end1))
			++res;
	}

	printf("%d\n", res);

	return 0;
}

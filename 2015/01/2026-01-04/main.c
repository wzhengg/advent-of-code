#include <stdio.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to open file\n");
		return 1;
	}

	int floor = 0;
	int i = 0;

	int c;
	while ((c = fgetc(fp)) != EOF) {
		switch (c) {
			case '(':
				++floor;
				break;
			case ')':
				--floor;
				break;
		}

		++i;

		if (floor == -1) {
			break;
		}
	}

	fclose(fp);

	printf("%d\n", i);

	return 0;
}

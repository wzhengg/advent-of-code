#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

#define LINES 300
#define MAXLEN 50

char lines[LINES][MAXLEN];

int getdiff(char *s) {
	int nsrc, nenc, i;

	nsrc = strlen(s) - 1;
	nenc = 6;

	for (i = 1; i < nsrc-1; ++i)
		switch (s[i]) {
			case '\\': case '"': nenc += 2; break;
			default: ++nenc; break;
		}

	return nenc - nsrc;
}

int solve(void) {
	int i, diff;

	diff = 0;
	for (i = 0; i < LINES; ++i) {
		diff += getdiff(lines[i]);
	}

	return diff;
}

int main(void) {
	FILE *fp;
	int i;

	if ((fp = fopen(FILENAME, "r")) == NULL)
		exit(1);

	for (i = 0; i < LINES; ++i)
		if (!fgets(lines[i], MAXLEN, fp))
			exit(1);

	fclose(fp);

	printf("%d\n", solve());

	return 0;
}

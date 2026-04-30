#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80

#define ISDIGIT(c) ('0' <= (c) && (c) <= '9')
#define ISALPHA(c) ('a' <= (c) && (c) <= 'z')

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp)
		exit(1);

	char line[MAXLINE];

	while (fgets(line, MAXLINE, fp)) {
		char *rp = line;
		while (!ISDIGIT(*rp))
			++rp;

		int id = atoi(rp);
		int shift = id % 26;

		for (char *lp = line; lp != rp; ++lp) {
			if (ISALPHA(*lp)) {
				*lp = ((*lp-'a'+shift) % 26) + 'a';
			}
		}

		*rp = '\0';

		printf("%s (%d)\n", line, id);
	}

	return 0;
}

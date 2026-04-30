#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80
#define NALPHA  26
#define MAXFREQ 60

#define ISDIGIT(c) ('0' <= (c) && (c) <= '9')

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp)
		exit(1);

	char line[MAXLINE];

	int res = 0;

	while (fgets(line, MAXLINE, fp)) {
		int count[NALPHA] = {0};

		char *lp;
		for (lp = line; *lp && !ISDIGIT(*lp); ++lp) {
			if ('a' <= *lp && *lp <= 'z')
				++count[*lp-'a'];
		}

		long bucket[MAXFREQ] = {0};
		for (int i = 0; i < NALPHA; ++i) {
			assert(count[i] < MAXFREQ);
			if (count[i])
				bucket[count[i]] |= 1<<i;
		}

		int id = atoi(lp);
		while (*lp && ISDIGIT(*lp))
			++lp;
		++lp;

		int n = 0;
		for (int i = MAXFREQ-1; i >= 0; --i) {
			if (!bucket[i]) continue;
			for (char c = 'a'; c <= 'z'; ++c) {
				if (!(bucket[i] & 1<<(c-'a')))
					continue;
				if (*lp++ != c || ++n == 5)
					goto end;
			}
		}
end:

		if (*lp == ']')
			res += id;
	}

	printf("%d", res);

	return 0;
}

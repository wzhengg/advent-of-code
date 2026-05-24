#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	char buf[MAXLINE];
	assert(fgets(buf, MAXLINE, fp));

	long mask = 0;

	int l, r;
	for (l = r = 0; buf[r]; ++r) {
		while (mask & (long)1<<(buf[r]-'a'))
			mask &= ~((long)1 << (buf[l++]-'a'));

		mask |= (long)1 << (buf[r]-'a');

		if (r-l+1 == 14)
			break;
	}

	printf("%d\n", r+1);

	return 0;
}

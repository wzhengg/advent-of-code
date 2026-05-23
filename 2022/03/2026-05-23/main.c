#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		exit(1);
	}

	int res = 0;

	char *line = NULL;
	size_t n = 0;
	ssize_t nread;

	while ((nread = getline(&line, &n, fp)) != -1) {
		char set[52] = {0};

		int i;
		for (i = 0; i < (nread-1)/2; ++i) {
			char c = line[i];
			if ('a' <= c && c <= 'z')
				set[c-'a'] = 1;
			else if ('A' <= c && c <= 'Z')
				set[c-'A'+26] = 1;
		}

		for (; i < nread-1; ++i) {
			char c = line[i];
			if ('a' <= c && c <= 'z' && set[c-'a']) {
				res += c-'a'+1;
				break;
			} else if ('A' <= c && c <= 'Z' && set[c-'A'+26]) {
				res += c-'A'+27;
				break;
			}
		}
	}

	printf("%d\n", res);

	return 0;
}

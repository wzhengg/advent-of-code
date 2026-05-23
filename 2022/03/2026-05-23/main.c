#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		exit(1);
	}

	int res = 0;
	char buf1[50], buf2[50], buf3[50];

	while (fgets(buf1, sizeof(buf1), fp)) {
		assert(fgets(buf2, sizeof(buf2), fp));
		assert(fgets(buf3, sizeof(buf3), fp));

		char set1[52] = {0};
		char set2[52] = {0};

		for (int i = 0; buf1[i] != '\n'; ++i) {
			char c = buf1[i];
			if ('a' <= c && c <= 'z')
				set1[c-'a'] = 1;
			else if ('A' <= c && c <= 'Z')
				set1[c-'A'+26] = 1;
		}
		for (int i = 0; buf2[i] != '\n'; ++i) {
			char c = buf2[i];
			if ('a' <= c && c <= 'z')
				set2[c-'a'] = 1;
			else if ('A' <= c && c <= 'Z')
				set2[c-'A'+26] = 1;
		}

		for (int i = 0; buf3[i] != '\n'; ++i) {
			char c = buf3[i];
			if ('a'<=c && c<='z' && set1[c-'a'] && set2[c-'a']) {
				res += c-'a'+1;
				break;
			} else if ('A'<=c && c<='Z' && set1[c-'A'+26] && set2[c-'A'+26]) {
				res += c-'A'+27;
				break;
			}
		}
	}

	printf("%d\n", res);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 32

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
		exit(1);

	char line1[MAXLINE], line2[MAXLINE], line3[MAXLINE];
	int a1, a2, a3;
	int b1, b2, b3;
	int c1, c2, c3;

	int res = 0;

	while (fgets(line1, MAXLINE, fp) != NULL) {
		if (fgets(line2, MAXLINE, fp) == NULL)
			exit(1);
		if (fgets(line3, MAXLINE, fp) == NULL)
			exit(1);

		if (sscanf(line1, "%d %d %d", &a1, &b1, &c1) != 3)
			exit(1);
		if (sscanf(line2, "%d %d %d", &a2, &b2, &c2) != 3)
			exit(1);
		if (sscanf(line3, "%d %d %d", &a3, &b3, &c3) != 3)
			exit(1);

		if (a1+a2 > a3 && a2+a3 > a1 && a1+a3 > a2)
			++res;
		if (b1+b2 > b3 && b2+b3 > b1 && b1+b3 > b2)
			++res;
		if (c1+c2 > c3 && c2+c3 > c1 && c1+c3 > c2)
			++res;
	}

	printf("%d", res);

	return 0;
}

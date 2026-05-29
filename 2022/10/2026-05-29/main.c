#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	int cycle = 1;
	int x = 1;
	int sum = 0;

	char buf[10];
	while (fgets(buf, sizeof(buf), fp)) {
		int oldcycle = cycle;
		int oldx = x;

		int v;
		switch (sscanf(buf, "addx %d", &v)) {
			case 1:
				cycle += 2;
				x += v;
				break;
			default:
				cycle += 1;
				break;
		}

		if ((cycle-20) % 40 == 0)
			sum += cycle * x;
		else if ((oldcycle+1-20) % 40 == 0)
			sum += (oldcycle+1) * oldx;
	}

	printf("%d\n", sum);

	return 0;
}

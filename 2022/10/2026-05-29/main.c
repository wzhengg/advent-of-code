#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	int cycle = 1;
	int x = 1;

	char buf[10];
	while (fgets(buf, sizeof(buf), fp)) {
		int drawpos = (cycle-1) % 40;
		if (x-1 <= drawpos && drawpos <= x+1)
			putchar('#');
		else
			putchar('.');

		if (drawpos == 39)
			putchar('\n');

		++cycle;

		int v;
		switch (sscanf(buf, "addx %d", &v)) {
			case 0: case EOF: continue;
		}

		int endcycle = cycle + 1;
		do {
			drawpos = (cycle-1) % 40;
			if (x-1 <= drawpos && drawpos <= x+1)
				putchar('#');
			else
				putchar('.');

			if (drawpos == 39)
				putchar('\n');

			++cycle;
		} while (cycle < endcycle);

		x += v;
	}

	return 0;
}

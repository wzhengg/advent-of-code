#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define LINES 300
#define LINESIZE 32

enum op { ON, OFF, TOGGLE };

struct coordinate {
	int r, c;
};

struct instruction {
	enum op op;
	struct coordinate topleft;
	struct coordinate botright;
};

void do_instruction(char grid[][N], struct instruction instr) {
	int left, right, top, bot, r, c;

	left = instr.topleft.c;
	right = instr.botright.c;
	top = instr.topleft.r;
	bot = instr.botright.r;

	for (r = top; r <= bot; r++) {
		for (c = left; c <= right; c++) {
			switch (instr.op) {
				case ON:
					grid[r][c]++;
					break;
				case OFF:
					if (grid[r][c] > 0)
						grid[r][c]--;
					break;
				case TOGGLE:
					grid[r][c] += 2;
					break;
			}
		}
	}
}

long solve(char grid[][N], struct instruction *instrs) {
	int i, r, c;
	long res;

	for (i = 0; i < LINES; i++)
		do_instruction(grid, instrs[i]);

	res = 0;
	for (r = 0; r < N; r++)
		for (c = 0; c < N; c++)
			res += grid[r][c];

	return res;
}

int main(void) {
	FILE *fp;
	char line[LINESIZE+2], grid[N][N];
	struct instruction instrs[LINES];
	int i;
	long res;

	fp = fopen("input.txt", "r");
	if (!fp)
		exit(1);


	for (i = 0; i < LINES; i++) {
		if (!fgets(line, LINESIZE+2, fp))
			exit(1);

		if (sscanf(line, "turn on %d,%d through %d,%d", &instrs[i].topleft.r, &instrs[i].topleft.c, &instrs[i].botright.r, &instrs[i].botright.c) == 4)
			instrs[i].op = ON;
		else if (sscanf(line, "turn off %d,%d through %d,%d\n", &instrs[i].topleft.r, &instrs[i].topleft.c, &instrs[i].botright.r, &instrs[i].botright.c) == 4)
			instrs[i].op = OFF;
		else if (sscanf(line, "toggle %d,%d through %d,%d\n", &instrs[i].topleft.r, &instrs[i].topleft.c, &instrs[i].botright.r, &instrs[i].botright.c) == 4)
			instrs[i].op = TOGGLE;
	}

	if (fclose(fp))
		exit(1);

	memset(grid, 0, sizeof(grid));
	res = solve(grid, instrs);
	printf("%ld\n", res);

	return 0;
}

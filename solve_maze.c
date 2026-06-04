#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define WALL '#'
#define PATH ' '
#define PLAYER '@'

enum DIRECTIONS {
	DOWN = 0,
	RIGHT,
	LEFT,
	UP
};

bool wait_input = false;

char **maze;
int w;
int h;

void print_help(void) {
	printf("Chame com pelo menos o nome do arquivo do labirinto, largura e altura (nesta ordem)\n");
	printf("Argumentos opcionais:\n");
	printf("-w - Espera input do usuário para avançar\n");
}

int get_args(int argc, char *argv[], FILE **maze_file) {
	int state = 0;
	for (int i = 1; i < argc; i++) {
		char *str = argv[i];
		if (strlen(str) == 2) {
			if (str[1] == 'w' && str[0] == '-') wait_input = true;
		}
		if (state == 0) {
			*maze_file = fopen(str, "rb");
			if (*maze_file == NULL) {
				fprintf(stderr, "%s file doest not exists\n", str);
				return state;
			}
			state++;
			continue;
		}

		if (state == 1) {
			w = atoi(str);
			state++;
			continue;
		}

		if (state == 2) {
			h = atoi(str);
			state++;
		}
	}
	return state;
}

bool is_valid(int x, int y) {
	return (x > 0 && y > 0 && x < (w - 1) && y < (h - 1) && maze[y][x] != WALL);
}

void print_maze() {
	printf("\e[1;1H\e[2J");
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	fflush(stdout);

	if (wait_input) getchar();
}

bool solve_maze(int x, int y) {
	maze[y][x] = PLAYER;
	print_maze();
	if (x == (w - 1) && y == (h - 2)) return true;
	int next_x, next_y;
	for (int i = 0; i < 4; i++) {
		if (i == DOWN) next_x = x, next_y = y + 1;
		if (i == LEFT) next_x = x - 1, next_y = y;
		if (i == RIGHT) next_x = x + 1, next_y = y;
		if (i == UP) next_x = x, next_y = y - 1;
		if (is_valid(next_x, next_y)) {
			maze[y][x] = PATH;
			if (solve_maze(next_x, next_y)) return true;
			maze[y][x] = PLAYER;
			print_maze();
		}
	}

	return false;
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		print_help();
		exit(1);
	}
	int state = 0;
	FILE *maze_file;
	char *grid;

	state = get_args(argc, argv, &maze_file);

	if (state == 1) {
		fprintf(stderr, "Not enough args");
		goto close_end;
	}

	if (state == 2) {
		fprintf(stderr, "Not enough args");
		goto close_end;
	}

	if (state != 3) { 
		fprintf(stderr, "Not enough args");
		goto error_end;
	}
	
	grid = (char *) malloc(sizeof(char) * w * h);
	maze = (char **) malloc(sizeof(char *) * h);

	for (int i = 0; i < h; i++) {
		maze[i] = &grid[i * w];
		fread(&maze[i][0], sizeof(char), w, maze_file);
		fgetc(maze_file);
	}
	fclose(maze_file);

	solve_maze(1, 1);

	free(grid);
	free(maze);
	end:
	exit(0);
	
	close_end:
	fclose(maze_file);
	error_end:
	exit(1);
}
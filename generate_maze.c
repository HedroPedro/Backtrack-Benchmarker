#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define PATH ' '
#define WALL '#'

char **maze;

int width = 0;
int height = 0;

bool is_valid(int x, int y) {
	return (x > 0 && x < (width - 1) && y > 0 && y < (height - 1) && maze[y][x] == WALL);
}

void generate_maze(int x, int y) {
	maze[y][x] = PATH;
	int dirs[4] = {0, 1, 2, 3};
	for(int i = 0; i < 4; i++) {
		int r = rand()%4;
		int temp = dirs[i];
		dirs[i] = dirs[r];
		dirs[r] = temp;
	}

	for (int i = 0; i < 4; i++) {
		int next_x = x;
		int next_y = y;
		int index = dirs[i];
		if (index == 0) next_y -= 2;
		if (index == 1) next_y += 2;
		if (index == 2) next_x += 2;
		if (index == 3) next_x -= 2;

		if (is_valid(next_x, next_y)) {
			maze[(y+next_y)/2][(x+next_x)/2] = PATH;
			generate_maze(next_x, next_y);
		}
	}

}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Try calling with width and height <seed>");
		exit(1);

	}

	width = atoi(argv[1]);
	height = atoi(argv[2]);
	maze = (char **) malloc(sizeof(char *) * height);
	char *grid = (char *) malloc(sizeof(char) * width * height);
	
	for (int i = 0; i < height; i++) {
		maze[i] = &grid[i*width];
		for(int j= 0; j < width; j++) {
			maze[i][j] = WALL;
		}
	}

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand(ts.tv_sec ^ ts.tv_nsec);

	generate_maze(1, 1);
	maze[height - 2][width - 1] = PATH;

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}

	free(grid);
	free(maze);
}

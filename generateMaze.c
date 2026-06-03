#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bool.h>

#define PATH ' '
#define WALL '#'

char **maze;

int width = 0;
int height = 0;

bool is_valid(int x, int y) {
	return (x > 0 && x < (width-1) && y > 0 && y < (height - 1) && maze[y][x] == WALL);
}

void generate_maze(int x, int y) {
	maze[y][x] = PATH;
	int dirs[4] = {0, 1, 2, 3};
	for(int i = 0; i < 4; i++) {
		int r = rand()%4;
		int temp = dir[i];
		dir[i] = dir[r];
		dir[r] = temp;
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
		printf("Try calling with width and height");
		exit(1);
	}
	width = argv[1];
	height = argv[2];
	maze = (char **) malloc(sizeof(char *) * height);
	char *grid = (char *) malloc(sizeof(char) * width * height);
	
	for (int i = 0; i < height; i++) {
		maze[i] = &grid[i*width];
	}

	free(grid);
	free(maze);
}

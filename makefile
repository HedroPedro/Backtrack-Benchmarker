CC=gcc
CFLAGS=-Wall -Wextra -g
BUILDDIR=bin

.PHONY: all clean
all: build

build: $(BUILDDIR)/generate_maze $(BUILDDIR)/solve_maze 

$(BUILDDIR)/generate_maze: generate_maze.c | $(BUILDDIR)
	$(CC) -o $@ $<

$(BUILDDIR)/solve_maze: solve_maze.c | $(BUILDDIR)
	$(CC) -o $@ $<

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -rf bin
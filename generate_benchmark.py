from subprocess import run
from pathlib import Path
import time
import statistics

if __name__ == "__main__":
	size = 5
	max_size = 103
	n = 50
	csv_gen = open("gen_mazes.csv", "w")
	csv_gen.write("size;mean_time;sd\n")
	while size < max_size:
		maze_str = f"maze_{size}x{size}"
		gen_time = [None] * n
		path = Path(maze_str)
		if not path.exists():
			path.mkdir()
		for i in range(n):
			with open(f"{maze_str}/{i}.maze", "w") as f:
				start = time.perf_counter_ns()
				run(["./bin/generate_maze", str(size), str(size)], stdout=f)
				end = time.perf_counter_ns() - start
				gen_time[i] = end
		mean = statistics.mean(gen_time)
		sd = statistics.pstdev(gen_time)
		csv_gen.write(f"{size**2};{mean};{sd}\n")
		size += 2
	csv_gen.close()
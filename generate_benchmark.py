from subprocess import run
from pathlib import Path
import time
import statistics

if __name__ == "__main__":
	size = 7
	max_size = 104
	n = 50
	csv = open("gen_mazes.csv", "w")
	csv.write("size;mean_time;sd\n")
	while size < max_size:
		maze_str = f"maze_{size}x{size}"
		variance = 0
		gen_time = [None] * n
		if not Path(maze_str).exists():
			Path(maze_str).mkdir()
		for i in range(n):
			with open(f"{maze_str}/{i}.maze", "w") as f:
				args = ["./bin/generate_maze", str(size), str(size)]
				start = time.perf_counter_ns()
				run(args, stdout=f)
				end = (time.perf_counter_ns() - start) / 1000
				gen_time[i] = end
		mean = statistics.mean(gen_time)
		sd = statistics.pstdev(gen_time)
		csv.write(f"{size**2};{mean:.3f};{sd:.3f}\n")
		size += 2
	csv.close()
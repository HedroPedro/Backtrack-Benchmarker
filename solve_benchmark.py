import re
import time
import statistics
from pathlib import Path
from subprocess import run

ANSI_CLEAR = "\033[H\033[2J"

if __name__ == "__main__":
	root = Path(".")
	dirs = [d for d in root.glob("maze*") if d.is_dir()]
	pattern = r"\d+"
	with open("solve_mazes.csv", "w") as solve_csv:
		solve_csv.write("size;mean_time;sd\n")
		for d in dirs:
			print(ANSI_CLEAR, end="", flush=True)
			w, h = re.findall(pattern, d.name)
			w = int(w)
			h = int(h)
			iter_dir = list(d.iterdir())
			solve_time = [None] * len(iter_dir)
			for f, i in zip(iter_dir, range(len(iter_dir))):
				start = time.perf_counter_ns()
				run(["./bin/solve_maze", f.absolute(), str(w), str(h)])
				end = (time.perf_counter_ns() - start) / 1000
				solve_time[i] = end
				print(ANSI_CLEAR, end="", flush=True)
			mean = statistics.mean(solve_time)
			sd = statistics.pstdev(solve_time)
			solve_csv.write(f"{w*h};{mean:.3f};{sd:.3f}\n")
			solve_csv.flush()
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
import numpy as np
import argparse

USE_NUMPY = 1

parser = argparse.ArgumentParser()
parser.add_argument("n", type=int, help="N number of files")
args = parser.parse_args()

def parse_dynamic_file(filename):
    frames = []

    with open(filename, "r") as f:
        lines = [line.strip() for line in f if line.strip()]

    i = 0

    while i < len(lines):
        n = int(lines[i])
        i += 1

        time_line = lines[i]
        t = float(time_line.split()[1])
        cfc = int(time_line.split()[2])
        i += 1

        for _ in range(n):
            i += 1

        frames.append((t, cfc))

    return frames

for i in range(args.n):
    INPUT_FILE = f"output/dynamic{i}.txt"
    frames = parse_dynamic_file(INPUT_FILE)

    time_long, cfcval_long = map(list, zip(*frames))

    time = [time_long[0]]
    cfcval = [cfcval_long[0]]

    for i in range(1, len(cfcval_long)):
        if cfcval_long[i] != cfcval_long[i - 1]:
            time.append(time_long[i])
            cfcval.append(cfcval_long[i])

    try:
        xline = np.linspace(0,int(time[-1]), int(time[-1] * 3))

        coef = np.polyfit(time,cfcval,1)
        poly1d_fn = np.poly1d(coef) 

        plt.plot(time,cfcval, 'yo', time, poly1d_fn(time), '--k')
        plt.show()
    except Exception as e:
        print("Error:", e)





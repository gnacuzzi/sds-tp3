import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
import numpy as np
import argparse

USE_NUMPY = 1

NUM_OF_N = [20,50,100,200,500]

# ==============================
# PARSER
# ==============================

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

N_vals = []
J_means = []
J_stds = []

for N in NUM_OF_N:
    plt.figure(figsize=(8, 5))

    # Generate distinct colors for each iteration Set1, tab10 Dark2
    colors = plt.cm.Set1(np.linspace(0, 1, args.n))
    J_values = []

    for idx in range(args.n):
        INPUT_FILE = f"output/{N}_dynamic{idx}.txt"
        frames = parse_dynamic_file(INPUT_FILE)

        time_long, cfcval_long = map(list, zip(*frames))

        # Keep only points where CFC changes
        time = [time_long[0]]
        cfcval = [cfcval_long[0]]

        for j in range(1, len(cfcval_long)):
            if cfcval_long[j] != cfcval_long[j - 1]:
                time.append(time_long[j])
                cfcval.append(cfcval_long[j])

        color = colors[idx]

        try:
            # Fit linear regression
            coef = np.polyfit(time, cfcval, 1)
            poly1d_fn = np.poly1d(coef)
            J_values.append(coef[0])

            # Scatter points
            plt.scatter(time, cfcval, color=color, s=15)

            # Extended regression line (full range)
            xline = np.linspace(0, 5, 200)
            plt.plot(
                xline,
                poly1d_fn(xline),
                color=color,
                linestyle="--",
                label=f"Run {idx} (J={coef[0]:.2f})"
            )

        except Exception as e:
            J_values.append(0)
            plt.scatter(time, cfcval, color=color, s=15,
                        label=f"Run {idx} (J=0)")
            print(f"Error in N={N}, run={idx}:", e)
    
    
    J_mean = np.mean(J_values)
    J_std = np.std(J_values, ddof=1)

    N_vals.append(N)
    J_means.append(J_mean)
    J_stds.append(J_std)

    plt.title(f"Cfc(t) and Linear Fit for N = {N}")
    plt.xlabel("Time")
    plt.ylabel("Cfc(t)")
    plt.legend(fontsize=8)
    plt.grid(alpha=0.3)

    plt.tight_layout()
    filename = f"images/Cfc_fit_N_{N}.png"
    plt.savefig(filename, dpi=600)
    plt.show()


#Plot J vs N
N_vals = np.array(N_vals)
J_means = np.array(J_means)
J_stds = np.array(J_stds)
plt.figure(figsize=(8, 5))

plt.errorbar(
    N_vals,
    J_means,
    yerr=J_stds,
    fmt='o-',
    capsize=5,
    capthick=1,
)

plt.fill_between(
    N_vals,
    J_means - J_stds,
    J_means + J_stds,
    alpha=0.15
)

plt.title("Average scanning rate ⟨J⟩ vs N")
plt.xlabel("N")
plt.ylabel("⟨J⟩")
plt.grid(alpha=0.3)

plt.tight_layout()
filename = "images/J_vs_N.png"
plt.savefig(filename, dpi=600)
plt.show()




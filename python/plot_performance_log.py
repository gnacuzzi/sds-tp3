import csv
import matplotlib.pyplot as plt

# Escalas logaritmicas (ejemplo tipico: log-log)
USE_LOG_X = True
USE_LOG_Y = True


ns = []
times = []

with open("output/performance.csv", "r") as f:
    reader = csv.reader(f)

    next(reader)  # skip header

    for row in reader:
        ns.append(int(row[0]))
        times.append(float(row[1]))


plt.figure(figsize=(8,5))

plt.plot(
    ns,
    times,
    marker="o",
    linestyle="-"
)

if USE_LOG_X:
    if any(n <= 0 for n in ns):
        raise ValueError("N must be > 0 to use logarithmic X scale")
    plt.xscale("log")

if USE_LOG_Y:
    if any(t <= 0 for t in times):
        raise ValueError("Execution times must be > 0 to use logarithmic Y scale")
    plt.yscale("log")

plt.xlabel("Number of Particles (N)", fontsize=14)
plt.ylabel("Execution Time (s)", fontsize=14)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)

#plt.ylim(0, max(times) * 1.5)
plt.tight_layout()

plt.savefig("images/performance_plot_log.png", dpi=300)

plt.show()
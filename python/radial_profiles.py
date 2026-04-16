import numpy as np
import matplotlib.pyplot as plt
import glob
import math

# =========================
# CONFIG
# =========================
dS = 0.2
R_MAX = 40  # radio del sistema
CENTER = np.array([0.0, 0.0])

# =========================
# PARSER
# =========================
def read_dynamic_file(filename):
    snapshots = []

    with open(filename, "r") as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        n = int(lines[i].strip())
        i += 1

        header = lines[i].split()
        t = float(header[1])
        i += 1

        particles = []

        for _ in range(n):
            parts = lines[i].split()
            x = float(parts[1])
            y = float(parts[2])
            vx = float(parts[3])
            vy = float(parts[4])
            state = int(parts[5])

            particles.append((x, y, vx, vy, state))
            i += 1

        snapshots.append((t, particles))

    return snapshots


# =========================
# COMPUTE RADIAL PROFILES
# =========================
def compute_profiles(snapshots):
    num_bins = int(R_MAX / dS)

    rho_acc = np.zeros(num_bins)
    v_acc = np.zeros(num_bins)
    count_acc = np.zeros(num_bins)

    for t, particles in snapshots:
        for (x, y, vx, vy, state) in particles:

            # solo frescas
            if state != 0:
                continue

            R = np.array([x, y])
            r = np.linalg.norm(R)

            if r == 0 or r >= R_MAX:
                continue

            # producto escalar
            dot = x * vx + y * vy

            # solo las que van hacia el centro
            if dot >= 0:
                continue

            bin_idx = int(r / dS)
            if bin_idx >= num_bins:
                continue

            # velocidad radial
            v_radial = dot / r

            rho_acc[bin_idx] += 1
            v_acc[bin_idx] += v_radial
            count_acc[bin_idx] += 1

    # =========================
    # PROMEDIOS
    # =========================
    rho = np.zeros(num_bins)
    v = np.zeros(num_bins)

    for i in range(num_bins):
        if count_acc[i] > 0:
            v[i] = v_acc[i] / count_acc[i]

        # densidad = cantidad / área
        r_inner = i * dS
        r_outer = (i + 1) * dS
        area = math.pi * (r_outer**2 - r_inner**2)

        rho[i] = rho_acc[i] / area

    Jin = rho * np.abs(v)

    S = np.arange(num_bins) * dS

    return S, rho, v, Jin


# =========================
# MAIN (MULTIPLE RUNS)
# =========================
def process_N(n):
    pattern = f"output/{n}_dynamic*.txt"
    files = sorted(glob.glob(pattern))

    all_rho = []
    all_v = []
    all_J = []

    for file in files:
        print(f"Processing {file}")
        snapshots = read_dynamic_file(file)

        S, rho, v, Jin = compute_profiles(snapshots)

        all_rho.append(rho)
        all_v.append(v)
        all_J.append(Jin)

    # promedio entre realizaciones
    rho_mean = np.mean(all_rho, axis=0)
    v_mean = np.mean(all_v, axis=0)
    J_mean = np.mean(all_J, axis=0)

    return S, rho_mean, v_mean, J_mean


# =========================
# PLOT
# =========================
def plot_profiles(S, rho, v, J, n):
    plt.figure(figsize=(8,5))

    plt.plot(S, rho, label=r"$\langle \rho_f^{\mathrm{in}}\rangle(S)$")
    plt.plot(S, np.abs(v), label=r"$\left|\langle v_f^{\mathrm{in}}\rangle(S)\right|$")
    plt.plot(S, J, label=r"$J_{\mathrm{in}}(S)$")

    plt.xlabel("S (distance from center)", fontsize=14)
    plt.ylabel("Value", fontsize=14)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)

    plt.legend(fontsize=12)
    plt.tight_layout()

    plt.savefig(f"images/radial_profiles_N{n}.png", dpi=300)
    plt.show()


# =========================
# ENTRY POINT
# =========================
if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print("Usage: python radial_profiles.py N")
        exit(1)

    N = int(sys.argv[1])

    S, rho, v, J = process_N(N)

    plot_profiles(S, rho, v, J, N)

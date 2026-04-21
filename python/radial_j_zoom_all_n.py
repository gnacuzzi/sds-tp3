import glob
import os

import matplotlib
import numpy as np

matplotlib.use("Agg")
import matplotlib.pyplot as plt

from radial_profiles import process_N


# =========================
# CONFIG
# =========================
OUTPUT_DIR = "images"
X_MIN = 2.0
X_MAX = 5.0


def discover_ns():
    files = glob.glob("output/*_dynamic*.txt")
    ns = set()

    for path in files:
        base = os.path.basename(path)
        if "_dynamic" not in base:
            continue

        n_token = base.split("_dynamic", 1)[0]
        if n_token.isdigit():
            ns.add(int(n_token))

    return sorted(ns)


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    ns = discover_ns()
    if len(ns) == 0:
        print("No dynamic files found in output/")
        return

    fig, ax = plt.subplots(figsize=(9, 5))

    all_y_in_zoom = []
    plotted = 0

    for n in ns:
        print(f"Processing N = {n}")
        S, _, _, J = process_N(n)

        if S is None:
            continue

        mask = (S >= X_MIN) & (S <= X_MAX)
        if not np.any(mask):
            continue

        ax.plot(S[mask], J[mask], linewidth=2, label=f"N = {n}")
        all_y_in_zoom.append(J[mask])
        plotted += 1

    if plotted == 0:
        print("No valid J data found in the requested zoom interval")
        plt.close(fig)
        return

    ax.set_xlim(X_MIN, X_MAX)

    y_concat = np.concatenate(all_y_in_zoom)
    y_min = np.min(y_concat)
    y_max = np.max(y_concat)

    if y_max > y_min:
        pad = 0.08 * (y_max - y_min)
        ax.set_ylim(y_min - pad, y_max + pad)
    else:
        delta = 0.1 * (abs(y_min) + 1.0)
        ax.set_ylim(y_min - delta, y_max + delta)

    ax.set_xlabel("S (distance from center)", fontsize=14)
    ax.set_ylabel(r"$J_{\mathrm{in}}(S)$", fontsize=14)
    ax.tick_params(labelsize=12)
    ax.legend(fontsize=11)

    fig.tight_layout()
    out_path = f"{OUTPUT_DIR}/radial_Jin_zoom_all_N.png"
    fig.savefig(out_path, dpi=300)
    plt.close(fig)

    print(f"Saved: {out_path}")


if __name__ == "__main__":
    main()

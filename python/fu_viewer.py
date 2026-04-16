import matplotlib.pyplot as plt
import sys
import os

# ── Configuration ──────────────────────────────────────────────────────────────

INPUT_FILES = [
    "output/100_dynamic0.txt",
    # Add more files here; each gets its own line on the plot
]

# Figure
FIG_SIZE   = (10, 6)   # (width, height) in inches
DPI        = 150

# Font sizes
FONT_TITLE  = 16
FONT_LABELS = 14
FONT_TICKS  = 12
FONT_LEGEND = 12

# Colors — one per file; cycles if more files than colors
COLORS = ["#e63946", "#457b9d", "#2a9d8f", "#e9c46a", "#f4a261"]

# Line / marker style
LINE_STYLE  = "-"
LINE_WIDTH  = 1.5
MARKER      = "o"
MARKER_SIZE = 3

# Axes limits — set to None for auto
X_MIN, X_MAX = None, None
Y_MIN, Y_MAX = None, None

# Tick intervals — set to None for auto
X_TICK_INTERVAL = None   # e.g. 0.5
Y_TICK_INTERVAL = None   # e.g. 0.1

# Labels
TITLE   = "Fracción de uso (fu) en función del tiempo"
X_LABEL = "Tiempo (s)"
Y_LABEL = "fu"

# Output — set to None to only display
SAVE_PATH = "output/fu_plot.png"

# ── Helpers ────────────────────────────────────────────────────────────────────

def parse_fu(path: str):
    times, fus = [], []
    with open(path) as f:
        for line in f:
            parts = line.split()
            if parts and parts[0] == "t":
                times.append(float(parts[1]))
                fus.append(float(parts[-1]))
    return times, fus


def make_label(path: str) -> str:
    return os.path.splitext(os.path.basename(path))[0]

# ── Main ───────────────────────────────────────────────────────────────────────

def main():
    files = sys.argv[1:] if len(sys.argv) > 1 else INPUT_FILES

    fig, ax = plt.subplots(figsize=FIG_SIZE)

    for i, path in enumerate(files):
        color = COLORS[i % len(COLORS)]
        times, fus = parse_fu(path)
        ax.plot(
            times, fus,
            label=make_label(path),
            color=color,
            linestyle=LINE_STYLE,
            linewidth=LINE_WIDTH,
            marker=MARKER,
            markersize=MARKER_SIZE,
        )

    ax.set_title(TITLE, fontsize=FONT_TITLE)
    ax.set_xlabel(X_LABEL, fontsize=FONT_LABELS)
    ax.set_ylabel(Y_LABEL, fontsize=FONT_LABELS)
    ax.tick_params(labelsize=FONT_TICKS)

    if X_MIN is not None or X_MAX is not None:
        ax.set_xlim(X_MIN, X_MAX)
    if Y_MIN is not None or Y_MAX is not None:
        ax.set_ylim(Y_MIN, Y_MAX)

    if X_TICK_INTERVAL is not None:
        import numpy as np
        xlo, xhi = ax.get_xlim()
        ax.set_xticks(np.arange(xlo, xhi + X_TICK_INTERVAL, X_TICK_INTERVAL))
    if Y_TICK_INTERVAL is not None:
        import numpy as np
        ylo, yhi = ax.get_ylim()
        ax.set_yticks(np.arange(ylo, yhi + Y_TICK_INTERVAL, Y_TICK_INTERVAL))

    if len(files) > 1:
        ax.legend(fontsize=FONT_LEGEND)

    fig.tight_layout()

    if SAVE_PATH:
        fig.savefig(SAVE_PATH, dpi=DPI)
        print(f"Saved to {SAVE_PATH}")

    plt.show()


if __name__ == "__main__":
    main()

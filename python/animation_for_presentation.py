import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
import numpy as np


# ==============================
# CONFIG
# ==============================

INPUT_FILE = "output/500_dynamic.txt"
OUTPUT_VIDEO = "videos/500_animation_radial_2.mp4"

SYSTEM_RADIUS = 40
OBSTACLE_RADIUS = 1
PARTICLE_RADIUS = 1
VIEW_MARGIN = 1.2
USE_STATE_COLORS = True

# Guias radiales para visualizar capas S (seccion 1.4)
SHOW_RADIAL_GUIDES = True
RADIAL_GUIDES = [2, 5, 10, 20, 30]

# Resaltado especifico para la capa cercana a S = 2
HIGHLIGHT_S2_LAYER = True
TARGET_S = 2.0
DS = 0.2


# ==============================
# PARSER
# ==============================

def parse_dynamic_file(filename):
    frames = []

    with open(filename, "r") as f:
        lines = [line.strip() for line in f if line.strip()]

    i = 0

    while i < len(lines):
        n = int(lines[i])
        i += 1

        time_line = lines[i]
        time_tokens = time_line.split()
        t = float(time_tokens[1])
        cfc = int(time_tokens[2]) if len(time_tokens) > 2 else None
        i += 1

        particles = []

        for _ in range(n):
            vals = lines[i].split()

            particle = {
                "id": int(vals[0]),
                "x": float(vals[1]),
                "y": float(vals[2]),
                "vx": float(vals[3]),
                "vy": float(vals[4]),
                # Descomentar para volver a colorear por estado fresca/no fresca.
                "state": int(vals[5]),
            }

            particles.append(particle)
            i += 1

        frames.append((t, particles, cfc))

    return frames


# ==============================
# LOAD DATA
# ==============================

frames = parse_dynamic_file(INPUT_FILE)


# ==============================
# FIGURE SETUP
# ==============================

fig, ax = plt.subplots(figsize=(8, 8))

fig.subplots_adjust(left=0, right=1, bottom=0, top=1)

ax.set_xlim(-SYSTEM_RADIUS - VIEW_MARGIN, SYSTEM_RADIUS + VIEW_MARGIN)
ax.set_ylim(-SYSTEM_RADIUS - VIEW_MARGIN, SYSTEM_RADIUS + VIEW_MARGIN)
ax.set_aspect("equal")
ax.axis("off")

outer_circle = Circle(
    (0, 0),
    SYSTEM_RADIUS,
    fill=False,
    color="green",
    linewidth=4
)

inner_circle = Circle(
    (0, 0),
    OBSTACLE_RADIUS,
    fill=True,
    color="purple",
    linewidth=2
)

ax.add_patch(outer_circle)
ax.add_patch(inner_circle)

if SHOW_RADIAL_GUIDES:
    for r in RADIAL_GUIDES:
        if OBSTACLE_RADIUS < r < SYSTEM_RADIUS:
            guide_circle = Circle(
                (0, 0),
                r,
                fill=False,
                color="gray",
                linewidth=1,
                linestyle="--",
                alpha=0.5
            )
            ax.add_patch(guide_circle)

if HIGHLIGHT_S2_LAYER:
    s_bin_start = int(TARGET_S / DS) * DS
    s_bin_end = s_bin_start + DS

    s2_inner = Circle(
        (0, 0),
        s_bin_start,
        fill=False,
        color="orange",
        linewidth=2.5,
        alpha=0.9
    )
    s2_outer = Circle(
        (0, 0),
        s_bin_end,
        fill=False,
        color="orange",
        linewidth=2.5,
        alpha=0.9
    )
    ax.add_patch(s2_inner)
    ax.add_patch(s2_outer)

particle_patches = []

for _ in range(len(frames[0][1])):
    patch = Circle((0, 0), PARTICLE_RADIUS)
#    patch = Circle((0, 0), PARTICLE_RADIUS, color="green")
    ax.add_patch(patch)
    particle_patches.append(patch)

info_text = ax.text(
    -SYSTEM_RADIUS - 4,
    SYSTEM_RADIUS + 2,
    "",
    fontsize=12,
    ha="left",
    va="bottom",
    color="black"
)

# ==============================
# UPDATE FUNCTION
# ==============================

def update(frame_idx):
    t, particles, cfc = frames[frame_idx]

    fresh_count = 0
    used_count = 0
    s2_inward_fresh_count = 0

    s_bin_start = int(TARGET_S / DS) * DS
    s_bin_end = s_bin_start + DS

    for patch, p in zip(particle_patches, particles):
        x = p["x"]
        y = p["y"]
        vx = p["vx"]
        vy = p["vy"]

        patch.center = (x, y)

        if p["state"] == 0:
            fresh_count += 1
            if USE_STATE_COLORS:
                patch.set_color("green")
            else:
                patch.set_color("green")
        else:
            used_count += 1
            if USE_STATE_COLORS:
                patch.set_color("purple")
            else:
                patch.set_color("green")

        if HIGHLIGHT_S2_LAYER:
            r = np.hypot(x, y)
            radial_dot = x * vx + y * vy
            in_s2_layer = s_bin_start <= r < s_bin_end
            fresh_inward = p["state"] == 0 and radial_dot < 0

            if in_s2_layer and fresh_inward:
                patch.set_color("orange")
                s2_inward_fresh_count += 1

    info_lines = [f"t = {t:.3f}", f"Fresh = {fresh_count}", f"Used = {used_count}"]
    if cfc is not None:
        info_lines.append(f"Cfc(t) = {cfc}")
    if HIGHLIGHT_S2_LAYER:
        info_lines.append(f"S~2 fresh+inward = {s2_inward_fresh_count}")
    info_text.set_text("\n".join(info_lines))

    return particle_patches


# ==============================
# ANIMATION
# ==============================

ani = animation.FuncAnimation(
    fig,
    update,
    frames=len(frames),
    interval=50,
    blit=False
)

ani.save(OUTPUT_VIDEO, writer="ffmpeg", fps=20)
plt.show()

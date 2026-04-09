import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
import numpy as np


# ==============================
# CONFIG
# ==============================

INPUT_FILE = "output/dynamic.txt"

SYSTEM_RADIUS = 40
OBSTACLE_RADIUS = 1
PARTICLE_RADIUS = 1


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
        t = float(time_line.split()[1])
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
                "state": int(vals[5]),
            }

            particles.append(particle)
            i += 1

        frames.append((t, particles))

    return frames


# ==============================
# LOAD DATA
# ==============================

frames = parse_dynamic_file(INPUT_FILE)


# ==============================
# FIGURE SETUP
# ==============================

fig, ax = plt.subplots(figsize=(8, 8))

ax.set_xlim(-SYSTEM_RADIUS - 5, SYSTEM_RADIUS + 5)
ax.set_ylim(-SYSTEM_RADIUS - 5, SYSTEM_RADIUS + 5)
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

particle_patches = []

for _ in range(len(frames[0][1])):
    patch = Circle((0, 0), PARTICLE_RADIUS)
    ax.add_patch(patch)
    particle_patches.append(patch)



# ==============================
# UPDATE FUNCTION
# ==============================

def update(frame_idx):
    t, particles = frames[frame_idx]


    for patch, p in zip(particle_patches, particles):
        patch.center = (p["x"], p["y"])

        if p["state"] == 0:
            patch.set_color("green")
        else:
            patch.set_color("purple")

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

plt.show()

# TP3 - Event Driven Molecular Dynamics Simulation

This project simulates an event-driven molecular dynamics system for **Simulación de Sistemas TP3**.

The simulation is implemented in **C**, while visualization and animation are handled in **Python**.

---

# Project Structure

```bash
tp3/
│
├── Makefile
├── src/            # C source files
├── python/         # Python scripts for animation / plotting
├── bin/            # Compiled executable
├── obj/            # Object files
└── output/         # Simulation output files
```

---

# Requirements

## C Compiler
A C compiler with C11 support is required.

Example:
- gcc
- clang

## Python
Python 3 is required.

Install dependencies:

```bash
pip install matplotlib numpy
```

---

# Build and Run Simulation

To compile the project:

```bash
make
```

To run the simulation:

```bash
make run
```

This will:

- compile the C simulation,
- execute it,
- generate the dynamic simulation output file at:

```bash
output/dynamic.txt
```

---

# View Animation

To visualize the simulation:

```bash
python3 python/animation.py
```

This will open a matplotlib animation window showing:

- the outer circular boundary,
- the central obstacle,
- all particles in motion.

---

# Cleaning

Remove compiled files:

```bash
make clean
```

Remove compiled files and simulation outputs:

```bash
make fclean
```

---

# Notes

- Simulation parameters such as particle count, final time, and geometry constants can be modified in:

```bash
src/config.h
```

- Animation display settings can be modified in:

```bash
python/animation.py
```
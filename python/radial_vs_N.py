import numpy as np
import matplotlib.pyplot as plt
from radial_profiles import process_N  # reutilizamos tu código

# =========================
# CONFIG
# =========================
dS = 0.2
TARGET_S = 2.0

# lista de N que querés analizar
Ns = [30, 50, 100, 200, 500]  

# =========================
# MAIN
# =========================
rho_vals = []
v_vals = []
J_vals = []

for N in Ns:
    print(f"Processing N = {N}")

    S, rho, v, J = process_N(N)

    # encontrar bin más cercano a S = 2
    idx = int(TARGET_S / dS)

    rho_vals.append(rho[idx])
    v_vals.append(v[idx])
    J_vals.append(J[idx])


# =========================
# PLOT
# =========================
plt.figure(figsize=(8,5))

plt.plot(Ns, rho_vals, marker='o', label=r'$\langle \rho_f^{\mathrm{in}}\rangle(S\approx 2)$')
plt.plot(Ns, np.abs(v_vals), marker='o', label=r'$\left|\langle v_f^{\mathrm{in}}\rangle(S\approx 2)\right|$')
plt.plot(Ns, J_vals, marker='o', label=r'$J_{\mathrm{in}}(S\approx 2)$')

plt.xlabel("Number of Particles (N)", fontsize=14)
plt.ylabel("Value", fontsize=14)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)

plt.legend(fontsize=12)
plt.tight_layout()

plt.savefig("images/radial_vs_N.png", dpi=300)
plt.show()
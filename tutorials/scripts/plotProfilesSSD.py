#!/usr/bin/env python3
"""
Compare ABL profiles defined with a log law and a power law.

The log-law, k, epsilon, and omega profiles follow the OFJ review:
u(z)       = u_tau / kappa * ln((z + z0) / z0)
k(z)       = u_tau**2 / sqrt(C_mu)
epsilon(z) = u_tau**3 / (kappa * (z + z0))
omega(z)   = u_tau / (sqrt(beta_star) * kappa * (z + z0))

The power law is included only for velocity comparison:
u(z) = U_ref * (z / z_ref)**alpha
"""

from __future__ import annotations

import math
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

script_dir = Path(__file__).parent

# =============================================================================
# User inputs
# =============================================================================
z_ref = 6.0        # [m] reference height
U_ref = 10.0       # [m/s] reference velocity at z_ref
z0 = 0.01          # [m] aerodynamic roughness length
kappa = 0.40       # [-] von Karman constant

alpha = 0.13       # [-] power-law exponent

z_min = 0.1        # [m] keep > 0
z_max = 500.0      # [m]
n_points = 500

C_mu = 0.09
beta_star = 0.09


def friction_velocity(U_ref: float, z_ref: float, z0: float, kappa: float) -> float:
    if z_ref <= 0.0:
        raise ValueError("z_ref must be > 0.")
    if z0 <= 0.0:
        raise ValueError("z0 must be > 0.")
    if kappa <= 0.0:
        raise ValueError("kappa must be > 0.")
    return U_ref * kappa / math.log((z_ref + z0) / z0)


def u_log_profile(z: np.ndarray, u_tau: float, z0: float, kappa: float) -> np.ndarray:
    return (u_tau / kappa) * np.log((z + z0) / z0)


def u_power_profile(z: np.ndarray, U_ref: float, z_ref: float, alpha: float) -> np.ndarray:
    return U_ref * (z / z_ref) ** alpha


def k_profile(z: np.ndarray, u_tau: float, C_mu: float) -> np.ndarray:
    return np.full_like(z, u_tau**2 / math.sqrt(C_mu), dtype=float)


def epsilon_profile(z: np.ndarray, u_tau: float, z0: float, kappa: float) -> np.ndarray:
    return u_tau**3 / (kappa * (z + z0))


def omega_profile(z: np.ndarray, u_tau: float, z0: float, kappa: float, beta_star: float) -> np.ndarray:
    return u_tau / (math.sqrt(beta_star) * kappa * (z + z0))


def main() -> None:
    z = np.linspace(z_min, z_max, n_points)

    u_tau = friction_velocity(U_ref, z_ref, z0, kappa)

    u_log = u_log_profile(z, u_tau, z0, kappa)
    u_pow = u_power_profile(z, U_ref, z_ref, alpha)
    k = k_profile(z, u_tau, C_mu)
    eps = epsilon_profile(z, u_tau, z0, kappa)
    omg = omega_profile(z, u_tau, z0, kappa, beta_star)

    print("ABL input parameters")
    print("--------------------")
    print(f"z_ref      = {z_ref:.6g} m")
    print(f"U_ref      = {U_ref:.6g} m/s")
    print(f"z0         = {z0:.6g} m")
    print(f"kappa      = {kappa:.6g}")
    print(f"alpha      = {alpha:.6g}")
    print(f"u_tau      = {u_tau:.6g} m/s")
    print(f"k (const.) = {k[0]:.6g} m^2/s^2")

    plt.figure(figsize=(7, 6))
    plt.plot(u_log, z, label="Log law (Richards–Hoxey)")
    plt.plot(u_pow, z, "--", label=f"Power law (alpha = {alpha:g})", alpha=0.5)
    plt.axhline(z_ref, linestyle=":", linewidth=1.0, label=f"z_ref = {z_ref:g} m")
    plt.xlabel("Velocity, U [m/s]")
    plt.ylabel("Height, z [m]")
    plt.title("ABL velocity profiles")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(script_dir / "abl_velocity.png", dpi=200)

    plt.figure(figsize=(7, 6))
    #plt.xlim(0, 2)
    plt.plot(k, z, label="k (Richards-Hoxey)")
    plt.xlabel("Turbulent kinetic energy, k [m$^2$/s$^2$]")
    plt.ylabel("Height, z [m]")
    plt.title("ABL turbulent kinetic energy profile")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(script_dir / "abl_k_profile.png", dpi=200)

    plt.figure(figsize=(7, 6))
    #plt.xlim(0, 0.1)
    plt.plot(eps, z, label="epsilon (Richards-Hoxey)")
    plt.xlabel("Dissipation rate, epsilon [m$^2$/s$^3$]")
    plt.ylabel("Height, z [m]")
    plt.title("ABL epsilon profile")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(script_dir / "abl_epsilon_profile.png", dpi=200)

    plt.figure(figsize=(7, 6))
    plt.plot(omg, z, label="omega (Richards-Hoxey)")
    plt.xlabel("Specific dissipation rate, omega [1/s]")
    plt.ylabel("Height, z [m]")
    plt.title("ABL omega profile")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(script_dir / "abl_omega_profile.png", dpi=200)

    plt.show()


if __name__ == "__main__":
    main()

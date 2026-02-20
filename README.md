

# RANS-ABL-OpenFOAM

**Modelling of the atmospheric boundary layer (ABL) using Reynolds-averaged Navier–Stokes (RANS) equations in OpenFOAM**

This repository accompanies the OpenFOAM® Journal article: 

Batistić, I., Cindori, M., Krizmanić, S., Džijan, I., Juretić, F., Škvorc, P., & Kozmar, H. (2025). Steady RANS modeling of the atmospheric boundary layer: A systematic review and some practical guidelines, OpenFOAM® Journal, 
https://doi.org/10.51560/ofj.v6.166

The case files provided here reproduce and support the numerical setups discussed in the paper. They serve as ready-to-use templates for simulating the neutrally stratified atmospheric boundary layer in OpenFOAM and are intended for extension to more complex simulations, such as structural aerodynamics, pollutant dispersion, or wind engineering applications. These setups are particularly useful for researchers and engineers who are new to ABL modeling in OpenFOAM.

## **Features**

- **Shear stress-driven** ABL model,
- **Pressure-driven** ABL model,
- **Constant body force-driven** ABL model.
- **Pre-configured boundary conditions** for both successor and precursor domain techniques,
-  Example simulations for verification and validation.
- Compatible with **OpenFOAM v2406**.



## Getting Started

**Prerequisites**

- OpenFOAM v2406
- Linux or MacOS environment
- ParaView (for post-processing)
- Gnuplot (for automated plotting)

**Installation**

Download and extract the case files to your working directory:

```bash
tar -xzf RANS-ABL-OpenFOAM.tar.gz
```

The latest version of this repository is maintained at: 
https://github.com/iBatistic/RANS-ABL-OpenFOAM

Before compiling or running the cases, ensure that OpenFOAM v2406 is installed and sourced in your shell environment.
For example:

```bash
source /path/to/OpenFOAM-v2406/etc/bashrc
```

Then compile the custom code by running:

```bash
cd RANS-ABL-OpenFOAM
./Allwmake
```



## **Tutorial Cases Structure**

Three main directories represent the different ABL modeling approaches:

```bash
├── constantBodyForceDriven
│   ├── literature
│   └── precursor
├── pressureDriven
│   ├── literature
│   ├── precursor
│   └── successor
└── shearStressDriven
    ├── literature
    ├── precursor
    └── successor
```

#### Description 

- **`shearStressDriven`**: flow driven by prescribed shear stress on the top boundary.
- **`pressureDriven`**: flow driven by a pressure gradient.
- **`constantBodyForceDriven`**: flow driven by an applied body force in the momentum equation. 
- **`successor`** inlet profiles are explicitly prescribed and the outlet uses a zero-gradient condition. These cases are intended to be used directly for simulations that include buildings or other objects of interest.
- **`precursor`**  inlet and outlet patches use periodic boundary conditions. The resulting flow profiles are mapped to the actual simulations that include buildings or other objects of interest.
- **`literature`** reference data from published studies, used for validation.


The precursor/ directory contains two sub-methods:

```
├── precursor
    ├── cyclicInletOutlet
    └── zeroGradInletOutlet
```

- **`cyclicInletOutlet`** uses cyclic boundary conditions at inlet and outlet.
- **`zeroGradInletOutlet`** uses `zeroGradient` boundary conditions for flow profiles at inlet and outlet.

**Note:** Although zero-gradient conditions are justified due to horizontal homogeneity, they require more iterations for convergence:

- Successor cases: ~few thousand iterations
- Precursor (zero gradient): ~100,000 iterations
- Precursor (cyclic): ~50,000 iterations

#### Precursor and Successor Relationship

Simulations involving buildings, terrain, or other objects of interest should use the successor setup. The successor cases are designed to provide a fully developed ABL inflow for engineering applications and can be directly extended by adding the object of interest to the computational domain.

For the shear stress-driven and pressure-driven ABL approaches, analytical inlet profiles are available. The successor cases use these prescribed analytical profiles and can therefore be executed independently. Precursor cases are also provided for the shear stress-driven and pressure-driven approaches. If executed, the precursor simulations converge to the same velocity and turbulence profiles that are analytically prescribed in the successor setups. In this sense, running the precursor is optional and mainly serves as a consistency check.

For the constant body-force-driven ABL approach, no analytical inlet profiles are available. Therefore, a precursor simulation must be executed first to generate converged inflow profiles. Any successor simulation in this case depends on the profiles obtained from the precursor run.



## **Running the Case**

The cases in this repository are organised according to the structure described above.  Each modeling approach (shear stress-driven, pressure-driven, or body-force-driven) contains separate OpenFOAM tutorial cases for the precursor and/or successor techniques.  Choose the desired modeling approach and technique (for example: `shearStressDriven` → `successor`), then open a terminal inside that case directory, for example:

```bash
cd shearStressDriven/successor
```

Ensure that OpenFOAM v2406 is sourced in your environment, and execute the case using:

```
./Allrun
```

Optionally, the case can be run in parallel using parallel keyword:
```
./Allrun parallel
```

Each case includes an `Allclean` script to clean up generated simulation data. If Gnuplot is installed, velocity and turbulence plots will be generated automatically, showing profiles near the inlet and outlet boundaries. Literature data will also be included in the plots for comparison.

#### Running All Tutorial Cases

A top-level `Allrun` script is provided in the tutorial directory to execute all tutorial cases sequentially.

To run all cases one-by-one:

```bash
./Allrun
```

To execute all cases in parallel (each case using its internal parallel configuration):

```bash
./Allrun parallel
```

A corresponding `Allclean` script is also provided to remove generated simulation results from all tutorial cases:

```
./Allclean
```

The generated PDF files from automated post-processing can be located, for example, using `find . -name "*.pdf"` command.



## **Contributing**

Contributions are welcome! If you find issues, or would like to improve or extend these cases, please open an issue or submit a pull request to the [RANS-ABL-OpenFOAM](https://github.com/iBatistic/RANS-ABL-OpenFOAM) GitHub repository. If you use any part of this repository in your research or publication, please cite it appropriately.


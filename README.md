

# ABL-OpenFOAM

Case files for simulating the neutrally stratified atmospheric boundary layer (ABL) using different modeling approaches. Based on a commonly used benchmark, they are intended for use in more complex simulations; such as structural aerodynamics, pollutant dispersion, or wind engineering. These setups serve as practical examples, particularly for researchers and engineers new to ABL modeling in OpenFOAM.

## **Features**

- **Shear stress-driven** ABL model,
- **Pressure-driven** ABL model,
- **Body force-driven** ABL model.
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
tar -xzf ABL-OpenFOAM.tar.gz
```

Alternatively, a more up-to-date version may be available in the ABL-OpenFOAM GitHub repository.

Then source OpenFOAM and compile code in the `src/` directory:

```
cd ABL-OpenFOAM/src
openfoam2406
wmake
```

> Note: openfoam2406 is an alias for sourcing the etc/bashrc file of your OpenFOAM installation.

## **Cases Structure**

Three main directories represent the different ABL modeling approaches:

```bash
├── constantBodyForceDriven
│   ├── literature
│   ├── precursor
│   └── successor
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

- **`shearStressDriven/`**: flow driven by prescribed shear stress on the top boundary.
- **`pressureDriven/`**: flow driven by a pressure gradient.
- **`constantBodyForceDriven/`**: flow driven by an applied body force in the momentum equation.
- **`successor/`** inlet profiles are explicitly defined; the outlet uses a Neumann condition. This setup can be applied directly the actual simulation.
- **`precursor/`**  inlet and outlet patches use periodic boundary conditions. The resulting flow profiles are mapped to the actual simulation.
- **`litearature/`** reference data from published studies, used for validation.


The precursor/ directory contains two sub-methods:

```
├── precursor
    ├── cyclicInletOutlet
    └── zeroGradInletOutlet
```

- **`cyclicInletOutlet/`** uses cyclic boundary conditions at inlet and outlet
- **`zeroGradInletOutlet/`** uses `zeroGradient` boundary conditions for flow profiles at inlet and outlet

**Note:** Although zero-gradient conditions are justified due to horizontal homogeneity, they require more iterations for convergence:

- Successor cases: ~few thousand iterations
- Precursor (zero gradient): ~100,000 iterations
- Precursor (cyclic): ~50,000 iterations

## **Running the Case**

Navigate to the desired case folder, source OpenFOAM and run case using `./Allrun` script

```
openfoam2406
./Allrun
```

Optionally, case can be run in parallel using parallel keyword:
```
./Allrun parallel
```

Each case includes an `Allclean` script to clean up generated simulation data. If Gnuplot is installed, velocity and turbulence plots will be generated automatically, showing profiles near the inlet and outlet boundaries. Literature data will also be included in the plots for comparison.


## **Contributing**

Contributions are welcome! If you find issues, or would like to improve or extend these cases, please open an issue or submit a pull request to the ABL-OpenFOAM GitHub repository.
If you use any part of this repository in your research or publication, please cite it appropriately.


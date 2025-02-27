

# ABL-OpenFOAM

This repository contains OpenFOAM case files for simulating the neutrally stratified atmospheric boundary layer (ABL) using different modeling approaches.
The case setups are designed for computational wind engineering applications, including urban wind studies, pollutant dispersion, and structural aerodynamics. 

## **Features** 

- **shear stress-driven** ABL case;
- Implementation of **pressure-driven** ABL, 
- Implementation of **body force-driven** ABL models. 
- **Pre-configured boundary conditions** for successor and precursor domain techniques.  
-  Example simulations for verification and validation. 
- Compatible with OpenFOAM v2312 and later. 
  

## Getting Started

**Prerequisites** 

- OpenFOAM v2312
- Linux environment (recommended)
- ParaView for post-processing

**Installation**

Clone the repository using:

```bash
git clone https://github.com:iBatistic/ABL-OpenFOAM.git
cd ABL-OpenFOAM/src
wmake libso
```

Navigate to the desired case folder, source OpenFOAM with `openfoam2312` and run desired case using `./Allrun` command.


## **Case Descriptions**

- **Shear Stress-Driven ABL**: Driven by a prescribed shear stress at the top boundary.
- **Pressure-Driven ABL**: Uses a pressure gradient to sustain the flow.
- **Body Force-Driven ABL**: Includes an additional forcing term to drive the flow.

Each case directory contains necessary `constant`, `system`, and `0` folders with proper boundary conditions.


## **References**

For more details on the methodology and theoretical background, refer to the paper:   Batistić et al., *Review of Atmospheric Boundary Layer Modeling Approaches with RANS*, OpenFOAM Journal, 2025.   
If you use these OpenFOAM case files in your research or projects, please cite the paper. 


## **Contributing**

Contributions are welcome! Please open an issue or submit a pull request if you would like to improve the cases.

Maintained by: Ivan Batistić  
Contact: ivan.batistic2@gmail.com   

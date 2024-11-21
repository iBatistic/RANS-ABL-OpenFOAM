/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2018 OpenFOAM Foundation
    Copyright (C) 2015-2021 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::atmBoundaryLayerPressureDriven

Group
    grpRASBoundaryConditions grpInletBoundaryConditions

Description
    Base class to set log-law type ground-normal inlet boundary conditions for
    wind velocity and turbulence quantities for homogeneous, two-dimensional,
    dry-air, equilibrium and neutral pressure driven  atmospheric boundary
    layer presented in:

    Reference:
    \verbatim
        Richards, P.J., Norris S.E. (2015)
        Appropriate boundary conditions for a pressure driven boundary layer.
        Journal of Wind Engineering and Industrial Aerodynamics (JWEIA)
        142, 43-52.
    \endverbatim


    The ground-normal profile expressions are:

    \f[
        u = \frac{u_{\tau}}{\kappa}  \left( \ln\left(\frac{z}{z_0}\right)
            +  C_{U1}\left(\frac{z}{H}\right)
            + C_{U2}\left(\frac{z}{H}\right)^2
            + C_{U3}\left(\frac{z}{H}\right)^3
            + C_{U4}\left(\frac{z}{H}\right)^4  \right)
    \f]

    \f[
        v = w = 0
    \f]

    \f[
        k = u_{\tau}^2  \left(  C_{k1} + C_{k2}\left(1-\frac{z}{H}\right)^2
            + C_{k3}\left(1-\frac{z}{H}\right)^4
            + C_{k4}\left(1-\frac{z}{H}\right)^6   \right)
    \f]

    \f[
        \epsilon = \frac{C_{\mu} k(z)^2}{\kappa u_{\tau} z} \left( 1
            + (1+C_{U1})\left(\frac{z}{H}\right)
            + (1+C_{U1}+2C_{U2})\left(\frac{z}{H}\right)^2
            + (1+C_{U1}+2C_{U2}+3C_{U3})\left(\frac{z}{H}\right)^3 \right)
    \f]

    \f[
        \omega = \frac{ k(z)^2}{\kappa u_{\tau} z} \left( 1
            + (1+C_{U1})\left(\frac{z}{H}\right)
            + (1+C_{U1}+2C_{U2})\left(\frac{z}{H}\right)^2
            + (1+C_{U1}+2C_{U2}+3C_{U3})\left(\frac{z}{H}\right)^3  \right)
    \f]


    where
    \vartable
      u        | Ground-normal streamwise flow speed profile          [m/s]
      v        | Spanwise flow speed                                  [m/s]
      w        | Ground-normal flow speed                             [m/s]
      k        | Ground-normal turbulent kinetic energy (TKE) profile [m^2/s^2]
      \epsilon | Ground-normal TKE dissipation rate profile           [m^2/s^3]
      \omega   | Ground-normal specific dissipation rate profile      [m^2/s^3]
      u^*      | Friction velocity                                    [m/s]
      \kappa   | von Kármán constant                                  [-]
      C_\mu    | Empirical model constant                             [-]
      z        | Ground-normal coordinate component                   [m]
      z_0      | Aerodynamic roughness length                         [m]
      Cu       | Velocity profile constant                            [-]
      Ck       | Turbulent kinetic energy profile constant            [-]
      hd       | Domain height                                        [m]
    \endvartable


Usage
    Example of the entries provided for the inherited boundary conditions:
    \verbatim
    inlet
    {
        // Mandatory and other optional entries
        ...

        // Mandatory (inherited) entries (runtime modifiable)
        flowDir         (1 0 0);
        zDir            (0 0 1);
        Ck1		  0.921;
        Ck2		  3.533;
        Ck3		 -1.926;
        Ck4		  0.805;
        Cu1               0.528;
        Cu2               0.385;
        Cu3               -1.09;
        Cu4               0.243;
        hd		   3.57;
        uTau		   1.31;
        z0          uniform 0.1;

        // Optional (inherited) entries (unmodifiable)
        kappa           0.40;
        Cmu             0.09;
        initABL         true;
        phi             phi;

        // Conditional mandatory (inherited) entries (runtime modifiable)
        value           uniform 0;    // when initABL=false
    }
    \endverbatim

See also
    - Foam::atmBoundaryLayerPDInletVelocityFvPatchVectorField
    - Foam::atmBoundaryLayerPDInletKFvPatchScalarField
    - Foam::atmBoundaryLayerPDInletEpsilonFvPatchScalarField
    - Foam::atmBoundaryLayerPDInletOmegaFvPatchScalarField

SourceFiles
    atmBoundaryLayerPD.C

\*---------------------------------------------------------------------------*/

#ifndef atmBoundaryLayerPD_H
#define atmBoundaryLayerPD_H

#include "fvPatchFields.H"
#include "Function1.H"
#include "PatchFunction1.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class atmBoundaryLayerPD Declaration
\*---------------------------------------------------------------------------*/

class atmBoundaryLayerPD
{
protected:

    // Protected Data

        //- Flag to initialise profiles with the theoretical ABL expressions,
        //- otherwise initialises by using "value" entry content
        bool initABL_;


private:

    // Private Data

        //- Velocity profile constant
        const scalar Cu1_;

	//- Velocity profile constant
        const scalar Cu2_;

	//- Velocity profile constant
        const scalar Cu3_;

	//- Velocity profile constant
        const scalar Cu4_;

        //- Tke profile constant
        const scalar Ck1_;

	//- Tke profile constant
        const scalar Ck2_;

	//- Tke profile constant
        const scalar Ck3_;

	//- Tke profile constant
        const scalar Ck4_;

        //- von Kármán constant
        const scalar kappa_;

        //- Empirical model constant
        const scalar Cmu_;

        //- Domain height
        const scalar hd_;

        //- Friction velocity
        const scalar uTau_;

        //- Minimum coordinate vector of this patch
        const vector ppMin_;

        //- Reference to the time database
        const Time& time_;

        //- Reference to the patch
        const polyPatch& patch_;

        //- Streamwise flow direction
        autoPtr<Function1<vector>> flowDir_;

        //- Direction of the ground-normal coordinate
        autoPtr<Function1<vector>> zDir_;

        //- Surface roughness length
        autoPtr<PatchFunction1<scalar>> z0_;


public:

    // Constructors

        //- Construct null from time
        atmBoundaryLayerPD(const Time& time, const polyPatch& pp);

        //- Construct from the time database and dictionary
        atmBoundaryLayerPD
        (
            const Time& time,
            const polyPatch& pp,
            const dictionary& dict
        );

        //- Construct by mapping given atmBoundaryLayerPD onto a new patch
        atmBoundaryLayerPD
        (
            const atmBoundaryLayerPD& abl,
            const fvPatch& patch,
            const fvPatchFieldMapper& mapper
        );

        //- Construct as copy
        atmBoundaryLayerPD(const atmBoundaryLayerPD&);


    // Member Functions

        // Access

            //- Return flow direction
            vector flowDir() const;

            //- Return the ground-normal direction
            vector zDir() const;


        // Mapping

            //- Map (and resize as needed) from self given a mapping object
            void autoMap(const fvPatchFieldMapper&);

            //- Reverse map the given fvPatchField onto this fvPatchField
            void rmap(const atmBoundaryLayerPD&, const labelList&);


        // Evaluation

            //- Return the velocity distribution for the ATM
            tmp<vectorField> U(const vectorField& pCf) const;

            //- Return the turbulent kinetic energy distribution for the ATM
            tmp<scalarField> k(const vectorField& pCf) const;

            //- Return the turbulent dissipation rate distribution for the ATM
            tmp<scalarField> epsilon(const vectorField& pCf) const;

            //- Return the specific dissipation rate distribution for the ATM
            tmp<scalarField> omega(const vectorField& pCf) const;


        //- Write
        void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

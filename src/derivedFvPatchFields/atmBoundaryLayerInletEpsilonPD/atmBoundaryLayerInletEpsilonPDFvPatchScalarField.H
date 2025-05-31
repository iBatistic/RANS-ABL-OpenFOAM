/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2018 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
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
    Foam::atmBoundaryLayerInletEpsilonPDFvPatchScalarField

Group
    grpRASBoundaryConditions grpInletBoundaryConditions

Description
    This boundary condition specifies a dissipation rate profile at inlet
    for simulation of homogeneous, two-dimensiona, equilibrium and neutral
    atmospheric pressure driven boundary layer.
    Boundary condition is presented in:
    Richards, P.J., Norris S.E. (2015)
    Appropriate boundary conditions for a pressure driven boundary layer.
    Journal of Wind Engineering and Industrial Aerodynamics (JWEIA)
    142, 43-52.

    The ground-normal \c epsilon profile expression is given in Eq. 43.

Usage
    Example of the boundary condition specification:
    \verbatim
    inlet
    {
        // Mandatory entries (unmodifiable)
        type            atmBoundaryLayerInletEpsilonPD;

        // Mandatory/Optional (inherited) entries (unmodifiable)
        ...
    }
    \endverbatim

    where the entries mean:
    \table
      Property  | Description                             | Type | Reqd | Deflt
      type      | Type name: atmBoundaryLayerInletEpsilonPD | word | yes  | -
    \endtable

    The inherited entries are elaborated in:
     - \link atmBoundaryLayerPD.H \endlink
     - \link inletOutletFvPatchField.H \endlink

See also
    - Foam::atmBoundaryLayerPD
    - Foam::atmBoundaryLayerInletKPDFvPatchScalarField
    - Foam::atmBoundaryLayerInletOmegaPDFvPatchScalarField
    - Foam::atmBoundaryLayerInletVelocityPDFvPatchVectorField

SourceFiles
    atmBoundaryLayerInletEpsilonPDFvPatchScalarField.C

Author

w
\*---------------------------------------------------------------------------*/

#ifndef atmBoundaryLayerInletEpsilonPDFvPatchScalarField_H
#define atmBoundaryLayerInletEpsilonPDFvPatchScalarField_H

#include "fvPatchFields.H"
#include "inletOutletFvPatchFields.H"
#include "atmBoundaryLayerPD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
        Class atmBoundaryLayerInletEpsilonPDFvPatchScalarField Declaration
\*---------------------------------------------------------------------------*/

class atmBoundaryLayerInletEpsilonPDFvPatchScalarField
:
    public inletOutletFvPatchScalarField,
    public atmBoundaryLayerPD
{

public:

    //- Runtime type information
    TypeName("atmBoundaryLayerInletEpsilonPD");


    // Constructors

        //- Construct from patch and internal field
        atmBoundaryLayerInletEpsilonPDFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        atmBoundaryLayerInletEpsilonPDFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //- atmBoundaryLayerInletEpsilonPDFvPatchScalarField onto a new patch
        atmBoundaryLayerInletEpsilonPDFvPatchScalarField
        (
            const atmBoundaryLayerInletEpsilonPDFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new atmBoundaryLayerInletEpsilonPDFvPatchScalarField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        atmBoundaryLayerInletEpsilonPDFvPatchScalarField
        (
            const atmBoundaryLayerInletEpsilonPDFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new atmBoundaryLayerInletEpsilonPDFvPatchScalarField(*this, iF)
            );
        }


    // Member Functions

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        // Mapping

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchScalarField&,
                const labelList&
            );


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

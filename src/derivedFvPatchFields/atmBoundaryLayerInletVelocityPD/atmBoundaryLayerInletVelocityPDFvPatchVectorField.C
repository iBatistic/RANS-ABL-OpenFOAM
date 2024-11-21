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

\*---------------------------------------------------------------------------*/

#include "atmBoundaryLayerInletVelocityPDFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

atmBoundaryLayerInletVelocityPDFvPatchVectorField::
atmBoundaryLayerInletVelocityPDFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    inletOutletFvPatchVectorField(p, iF),
    atmBoundaryLayerPD(iF.time(), p.patch())
{}


atmBoundaryLayerInletVelocityPDFvPatchVectorField::
atmBoundaryLayerInletVelocityPDFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    inletOutletFvPatchVectorField(p, iF),
    atmBoundaryLayerPD(iF.time(), p.patch(), dict)
{
    phiName_ = dict.getOrDefault<word>("phi", "phi");

    refValue() = U(patch().Cf());
    refGrad() = Zero;
    valueFraction() = 1;

    if (!initABL_)
    {
        this->readValueEntry(dict, IOobjectOption::MUST_READ);
    }
    else
    {
        vectorField::operator=(refValue());
        initABL_ = false;
    }
}


atmBoundaryLayerInletVelocityPDFvPatchVectorField::
atmBoundaryLayerInletVelocityPDFvPatchVectorField
(
    const atmBoundaryLayerInletVelocityPDFvPatchVectorField& pvf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    inletOutletFvPatchVectorField(pvf, p, iF, mapper),
    atmBoundaryLayerPD(pvf, p, mapper)
{}


atmBoundaryLayerInletVelocityPDFvPatchVectorField::
atmBoundaryLayerInletVelocityPDFvPatchVectorField
(
    const atmBoundaryLayerInletVelocityPDFvPatchVectorField& pvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    inletOutletFvPatchVectorField(pvf, iF),
    atmBoundaryLayerPD(pvf)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void atmBoundaryLayerInletVelocityPDFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    refValue() = U(patch().Cf());

    inletOutletFvPatchVectorField::updateCoeffs();
}


void atmBoundaryLayerInletVelocityPDFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    inletOutletFvPatchVectorField::autoMap(m);
    atmBoundaryLayerPD::autoMap(m);
}


void atmBoundaryLayerInletVelocityPDFvPatchVectorField::rmap
(
    const fvPatchVectorField& pvf,
    const labelList& addr
)
{
    inletOutletFvPatchVectorField::rmap(pvf, addr);

    const atmBoundaryLayerInletVelocityPDFvPatchVectorField& blpvf =
        refCast<const atmBoundaryLayerInletVelocityPDFvPatchVectorField>(pvf);

    atmBoundaryLayerPD::rmap(blpvf, addr);
}


void atmBoundaryLayerInletVelocityPDFvPatchVectorField::write(Ostream& os) const
{
    fvPatchField<vector>::write(os);
    os.writeEntryIfDifferent<word>("phi", "phi", phiName_);
    atmBoundaryLayerPD::write(os);
    fvPatchField<vector>::writeValueEntry(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchVectorField,
    atmBoundaryLayerInletVelocityPDFvPatchVectorField
);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

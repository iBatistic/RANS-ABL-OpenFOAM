/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2014-2016 OpenFOAM Foundation
    Copyright (C) 2018-2022 OpenCFD Ltd.
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

#include "atmBoundaryLayerPD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

atmBoundaryLayerPD::atmBoundaryLayerPD(const Time& time, const polyPatch& pp)
:
    initABL_(false),
    Cu1_(0.0),
    Cu2_(0.0),
    Cu3_(0.0),
    Cu4_(0.0),
    Ck1_(0.0),
    Ck2_(0.0),
    Ck3_(0.0),
    Ck4_(0.0),
    kappa_(0.40),
    Cmu_(0.09),
    hd_(0.0),
    uTau_(0.0),
    ppMin_((boundBox(pp.localPoints())).min()),
    time_(time),
    patch_(pp),
    flowDir_(nullptr),
    zDir_(nullptr),
    z0_(nullptr)
{}


atmBoundaryLayerPD::atmBoundaryLayerPD
(
    const Time& time,
    const polyPatch& pp,
    const dictionary& dict
)
:
    initABL_(dict.getOrDefault<bool>("initABL", true)),
    Cu1_(dict.getOrDefault("Cu1", 0.528)),
    Cu2_(dict.getOrDefault("Cu2", 0.385)),
    Cu3_(dict.getOrDefault("Cu3", -1.09)),
    Cu4_(dict.getOrDefault("Cu4", 0.243)),
    Ck1_(dict.getOrDefault("Ck1", 0.921)),
    Ck2_(dict.getOrDefault("Ck2", 3.533)),
    Ck3_(dict.getOrDefault("Ck3", -1.926)),
    Ck4_(dict.getOrDefault("Ck4", 0.805)),
    kappa_
    (
        dict.getCheckOrDefault<scalar>("kappa", 0.4, scalarMinMax::ge(SMALL))
    ),
    Cmu_(dict.getCheckOrDefault<scalar>("Cmu", 0.09, scalarMinMax::ge(SMALL))),
    hd_(dict.get<scalar>("hd")),
    uTau_(dict.get<scalar>("uTau")),
    ppMin_((boundBox(pp.localPoints())).min()),
    time_(time),
    patch_(pp),
    flowDir_(Function1<vector>::New("flowDir", dict, &time)),
    zDir_(Function1<vector>::New("zDir", dict, &time)),
    z0_(PatchFunction1<scalar>::New(pp, "z0", dict))
{
    Info<<"ABL model constants:" << endl;
    Info<<"\tC_U1: " << Cu1_ << endl;
    Info<<"\tC_U2: " << Cu2_ << endl;
    Info<<"\tC_U3: " << Cu3_ << endl;
    Info<<"\tC_U4: " << Cu4_ << endl;
    Info<<"\tC_k1: " << Ck1_ << endl;
    Info<<"\tC_k2: " << Ck2_ << endl;
    Info<<"\tC_k3: " << Ck3_ << endl;
    Info<<"\tC_k4: " << Ck4_ << endl;
    Info<<"\thd: " << hd_ << endl;
    Info<<"\tuTau: " << uTau_ << endl;
    Info<<"\tkappa: " << kappa_ << endl;
    Info<<"\tC_mu: " << Cmu_ << endl;
}


atmBoundaryLayerPD::atmBoundaryLayerPD
(
    const atmBoundaryLayerPD& abl,
    const fvPatch& patch,
    const fvPatchFieldMapper& mapper
)
:
    initABL_(abl.initABL_),
    Cu1_(abl.Cu1_),
    Cu2_(abl.Cu2_),
    Cu3_(abl.Cu3_),
    Cu4_(abl.Cu4_),
    Ck1_(abl.Ck1_),
    Ck2_(abl.Ck2_),
    Ck3_(abl.Ck3_),
    Ck4_(abl.Ck4_),
    kappa_(abl.kappa_),
    Cmu_(abl.Cmu_),
    hd_(abl.hd_),
    uTau_(abl.uTau_),
    ppMin_(abl.ppMin_),
    time_(abl.time_),
    patch_(patch.patch()),
    flowDir_(abl.flowDir_.clone()),
    zDir_(abl.zDir_.clone()),
    z0_(abl.z0_.clone(patch_))
{}


atmBoundaryLayerPD::atmBoundaryLayerPD(const atmBoundaryLayerPD& abl)
:
    initABL_(abl.initABL_),
    Cu1_(abl.Cu1_),
    Cu2_(abl.Cu2_),
    Cu3_(abl.Cu3_),
    Cu4_(abl.Cu4_),
    Ck1_(abl.Ck1_),
    Ck2_(abl.Ck2_),
    Ck3_(abl.Ck3_),
    Ck4_(abl.Ck4_),
    kappa_(abl.kappa_),
    Cmu_(abl.Cmu_),
    hd_(abl.hd_),
    uTau_(abl.uTau_),
    ppMin_(abl.ppMin_),
    time_(abl.time_),
    patch_(abl.patch_),
    flowDir_(abl.flowDir_.clone()),
    zDir_(abl.zDir_.clone()),
    z0_(abl.z0_.clone(patch_))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

vector atmBoundaryLayerPD::flowDir() const
{
    const scalar t = time_.timeOutputValue();
    const vector dir(flowDir_->value(t));
    const scalar magDir = mag(dir);

    if (magDir < SMALL)
    {
        FatalErrorInFunction
            << "magnitude of " << flowDir_->name() << " = " << magDir
            << " vector must be greater than zero"
            << abort(FatalError);
    }

    return dir/magDir;
}


vector atmBoundaryLayerPD::zDir() const
{
    const scalar t = time_.timeOutputValue();
    const vector dir(zDir_->value(t));
    const scalar magDir = mag(dir);

    if (magDir < SMALL)
    {
        FatalErrorInFunction
            << "magnitude of " << zDir_->name() << " = " << magDir
            << " vector must be greater than zero"
            << abort(FatalError);
    }

    return dir/magDir;
}


void atmBoundaryLayerPD::autoMap(const fvPatchFieldMapper& mapper)
{
    if (z0_)
    {
        z0_->autoMap(mapper);
    }
}


void atmBoundaryLayerPD::rmap
(
    const atmBoundaryLayerPD& abl,
    const labelList& addr
)
{
    if (z0_)
    {
        z0_->rmap(abl.z0_(), addr);
    }
}


tmp<vectorField> atmBoundaryLayerPD::U(const vectorField& pCf) const
{
    const scalar t = time_.timeOutputValue();
    const scalarField z0(max(z0_->value(t), ROOTVSMALL));
    const vector groundMin = (zDir() & ppMin_)*zDir();

    scalarField Un
    (
        (uTau_/kappa_) *
        (
            Foam::log((zDir()&pCf)/z0)
          + Cu1_ * ((zDir()&pCf)/hd_)
          + Cu2_ * Foam::pow((zDir()&(pCf-groundMin))/hd_, 2)
          + Cu3_ * Foam::pow((zDir()&(pCf-groundMin))/hd_, 3)
          + Cu4_ * Foam::pow((zDir()&(pCf-groundMin))/hd_, 4)
        )
    );

    return flowDir()*Un;
}


tmp<scalarField> atmBoundaryLayerPD::k(const vectorField& pCf) const
{
    const scalar t = time_.timeOutputValue();
    const scalarField z0(max(z0_->value(t), ROOTVSMALL));
    const vector groundMin = (zDir() & ppMin_)*zDir();

    return
        sqr(uTau_) *
        (
            Ck1_
          + Ck2_*(Foam::pow((1.0-(zDir()&(pCf-groundMin))), 2))
          + Ck3_*(Foam::pow((1.0-(zDir()&(pCf-groundMin))), 4))
          + Ck4_*(Foam::pow((1.0-(zDir()&(pCf-groundMin))), 6))
        );
}


tmp<scalarField> atmBoundaryLayerPD::epsilon(const vectorField& pCf) const
{
    const scalar t = time_.timeOutputValue();
    const scalarField z0(max(z0_->value(t), ROOTVSMALL));
    const vector groundMin = (zDir() & ppMin_) * zDir();

    return (Cmu_*Foam::pow(k(pCf), 2)/(kappa_*uTau_*(zDir()&(pCf-groundMin)))) *
        (
            1
          + (1 + Cu1_) * ((zDir()&(pCf-groundMin))/hd_)
          + (1 + Cu1_ + 2*Cu2_) * pow(((zDir()&(pCf-groundMin))/hd_), 2)
          + (1 + Cu1_ + 2*Cu2_ + 3*Cu3_) * pow(((zDir()&(pCf-groundMin))/hd_), 3)
        );
}


tmp<scalarField> atmBoundaryLayerPD::omega(const vectorField& pCf) const
{
    const scalar t = time_.timeOutputValue();
    const scalarField z0(max(z0_->value(t), ROOTVSMALL));
    const vector groundMin = (zDir() & ppMin_) * zDir();

    return (k(pCf)/(kappa_*uTau_*(zDir()&(pCf-groundMin)))) *
        (
            1
          + (1 + Cu1_) * ((zDir()&(pCf-groundMin))/hd_)
          + (1 + Cu1_ + 2*Cu2_) * pow(((zDir()&(pCf-groundMin))/hd_), 2)
          + (1 + Cu1_ + 2*Cu2_ + 3*Cu3_) * pow(((zDir()&(pCf-groundMin))/hd_), 3)
        );
}


void atmBoundaryLayerPD::write(Ostream& os) const
{
    os.writeEntry("initABL", initABL_);
    os.writeEntry("Cu1", Cu1_);
    os.writeEntry("Cu2", Cu2_);
    os.writeEntry("Cu3", Cu3_);
    os.writeEntry("Cu4", Cu4_);
    os.writeEntry("Ck1", Ck1_);
    os.writeEntry("Ck2", Ck2_);
    os.writeEntry("Ck3", Ck3_);
    os.writeEntry("Ck4", Ck4_);
    os.writeEntry("kappa", kappa_);
    os.writeEntry("Cmu", Cmu_);
    os.writeEntry("hd", hd_);
    os.writeEntry("uTau", uTau_);
    if (flowDir_)
    {
        flowDir_->writeData(os);
    }
    if (zDir_)
    {
        zDir_->writeData(os);
    }
    if (z0_)
    {
        z0_->writeData(os) ;
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

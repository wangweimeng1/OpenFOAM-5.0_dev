/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
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
    Foam::phaseChangeTwoPhaseMixtures::SchnerrSauer

Description
    SchnerrSauer cavitation model.

    Reference:
    \verbatim
        Schnerr, G. H., And Sauer, J.,
        "Physical and Numerical Modeling of Unsteady Cavitation Dynamics",
        Proc. 4th International Conference on Multiphase Flow,
        New Orleans, U.S.A., 2001.
    \endverbatim

SourceFiles
    SchnerrSauer.C

\*--------------------------------------------------------------------*/

#ifndef Kinzel_H
#define Kinzel_H

#include "phaseChangeTwoPhaseMixtureNuc.H"

// * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace phaseChangeTwoPhaseMixturesNuc
{

/*--------------------------------------------------------------------*\
                              Class SchnerrSauer
\*--------------------------------------------------------------------*/

class Kinzel
:
    public phaseChangeTwoPhaseMixtureNuc
{
    // Private data

        //- Bubble number density
        //dimensionedScalar n_;

        //- Nucleation site diameter
        dimensionedScalar dNuc_;

        //- Condensation rate coefficient
        dimensionedScalar Cc_;

        //- Vapourisation rate coefficient
        dimensionedScalar Cv_;

        dimensionedScalar p0_;

        dimensionedScalar Pref_;

        //- Nucleation site volume-fraction
        tmp<volScalarField>alphaNuc(const volScalarField& n_) const;

        //- Reciprocal bubble radius
        tmp<volScalarField>C_infty() const;

        //- alpha Coefficient for Kinzel Model
        tmp<volScalarField>alphaLiqCoeff() const;

        //- alpha Coefficient for Vapor term in Kinzel Model
        tmp<volScalarField>alphaLiqCoeffVap() const;
   
        tmp<volScalarField>alphaGammaTermVap() const;

        //- Part of the condensation and vapourisation rates
        tmp<volScalarField> pCoeffCond(const volScalarField& p) const;

        //- Part of the vaporization rates
        tmp<volScalarField> pCoeffVap(const volScalarField& p) const;

        //- Term to calcualte pressure different with saturation pressure 
        tmp<volScalarField> pDiff(const volScalarField& p) const;
public:

    //- Runtime type information
    TypeName("Kinzel");


    // Constructors

        //- Construct from components
        Kinzel
        (
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~Kinzel()
    {}


    // Member Functions

        //- Return the mass condensation and vaporisation rates as a
        //  coefficient to multiply (1 - alphal) for the condensation rate
        //  and a coefficient to multiply  alphal for the vaporisation rate
        virtual Pair<tmp<volScalarField>> mDotAlphal() const;

        //- Return the mass condensation and vaporisation rates as coefficients
        //  to multiply (p - pSat)
        virtual Pair<tmp<volScalarField>> mDotP() const;
  
        virtual Pair<tmp<volScalarField>> pCoeffChange() const;
        //- Correct the SchnerrSauer phaseChange model
        virtual void correct();

        //- Read the transportProperties dictionary and update
        virtual bool read();

        //- Return constant access to the nuclei density values
        //const volScalarField& n_() const
	//{
	//    const volScalarField& n_ = alpha1_.db().lookupObject<volScalarField>("n_");
  	//    return n_;
        //}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace phaseChangeTwoPhaseMixtures
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

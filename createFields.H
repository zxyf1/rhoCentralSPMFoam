Info<< "Reading thermophysical properties\n" << endl;

autoPtr<psiThermo> pThermo
(
    psiThermo::New(mesh)
);
psiThermo& thermo = pThermo();

volScalarField& e = thermo.he();

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    thermo.rho()
);

volVectorField rhoU
(
    IOobject
    (
        "rhoU",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    rho*U
);

volScalarField rhoE
(
    IOobject
    (
        "rhoE",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    rho*(e + 0.5*magSqr(U))
);

surfaceScalarField pos
(
    IOobject
    (
        "pos",
        runTime.timeName(),
        mesh
    ),
    mesh,
    dimensionedScalar("pos", dimless, 1.0)
);

surfaceScalarField neg
(
    IOobject
    (
        "neg",
        runTime.timeName(),
        mesh
    ),
    mesh,
    dimensionedScalar("neg", dimless, -1.0)
);

surfaceScalarField phi("phi", fvc::flux(rhoU));

Info<< "Creating turbulence model\n" << endl;
autoPtr<compressible::turbulenceModel> turbulence
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        phi,
        thermo
    )
);

//newly added for SPM:
Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );


//volVectorField xx = mesh.C(); coordinate for cell center
volVectorField xx
 (
    IOobject
    (
        "xx",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh.C()
 );
xx = mesh.C();

dimensionedVector xi 
(
    "xi",
    dimLength,
    transportProperties.lookup("xi")
 );// position of rectangle center

dimensionedScalar Xi
(
 "Xi",
 dimLength,
 transportProperties.lookup("Xi")
 ); //smoothed profile thickness

dimensionedVector ab
(
    "ab",
    dimLength,
    transportProperties.lookup("ab")
 );// rectangle half length 


//volScalarField dx = mag(xi.x()-a.x()); 
volScalarField dx
(
        IOobject
        (
            "dx",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
      mag(xi.component(0)-ab.component(0)) 
);
dx = mag(xi.component(0)-ab.component(0)); 

//volScalarField dy = mag(xi.y()-a.y()); 
volScalarField dy
(
        IOobject
        (
            "dy",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
     mag(xi.component(1)-ab.component(1)) 
);
dy = mag(xi.component(1)-ab.component(1)); 

//volScalarField d = mag(xx-xi);
volScalarField d
(
        IOobject
        (
            "d",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
    mag(xx-xi)	
);
d = mag(xx-xi);	

#include "subIndicator.H"






































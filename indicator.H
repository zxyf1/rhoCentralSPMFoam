Info << "define the indicator phiPhi" << endl;

volScalarField phiPhi
(
        IOobject
        (
            "phiPhi",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        0.5*(tanh((fi)/Xi)+1.0)
);
phiPhi = 0.5*(tanh((fi)/Xi)+1.0);



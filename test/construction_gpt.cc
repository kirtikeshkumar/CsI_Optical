/*This is the main construction file where we assign all the attributes of the detector, the environment, and the material of the detector*/

// Including the construction header file
#include "construction.hh"
#include "detector.hh"
#include <cmath>

MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();
    
    xWorld = 0.25*m;
    yWorld = 0.25*m;
    zWorld = 0.25*m;
}

// The destructor function
MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    // G4NistManager to get the required elements
    G4NistManager *nist = G4NistManager::Instance();

    worldMat = nist->FindOrBuildMaterial("G4_Galactic"); // Defining world material
    CsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    Si = nist->FindOrBuildMaterial("G4_Si"); // Define Si material
    
    // Optical Properties of world
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    
    // Cesium Iodide (Tl doped)
    G4double fractionmass;
    G4double TlDopantMassFraction = 0.355;
    G4double CsIDopantMassFraction = 1.0 - TlDopantMassFraction;
    CsI_Tl = new G4Material("CsI_Tl", 4.51*g/cm3, 2);
    CsI_Tl->AddMaterial(CsI, fractionmass = CsIDopantMassFraction);
    CsI_Tl->AddElement(nist->FindOrBuildElement("Tl"), fractionmass = TlDopantMassFraction);
    
    // Optical Properties of CsI(Tl)
    G4double rindexCsI_Tl[2] = {1.79, 1.79};
    G4MaterialPropertiesTable *mptCsITl = new G4MaterialPropertiesTable();
    mptCsITl->AddProperty("RINDEX", energy, rindexCsI_Tl, 2);
    CsI_Tl->SetMaterialPropertiesTable(mptCsITl);
}

void MyDetectorConstruction::ConstructSetup()
{
    // Define the size of the scintillator
    solidScint = new G4Box("Scint", 115.0 * mm, 115.0 * mm, 5.0 * mm);
    logicScint = new G4LogicalVolume(solidScint, CsI_Tl, "logicScint");
    skin = new G4LogicalSkinSurface("skin", logicScint, mirrorSurface);
    physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.2*m), logicScint, "physScint", logicWorld, false, 1, true);
    
    // Scintillation properties for CsI(Tl)
    G4double energyScint[] = {1.77*eV, 3.47*eV};  // Light emission range
    G4double scintFast[] = {1.0, 1.0};  // Scintillation spectrum (normalized)
    G4double scintSlow[] = {0.8, 1.0};  // Slow component spectrum

    G4double yield = 54000./MeV;  // Typical light yield for CsI(Tl)
    G4double fastTimeConst = 1.0*ns;
    G4double slowTimeConst = 7.0*ns;

    G4MaterialPropertiesTable *mptCsITl = new G4MaterialPropertiesTable();
    mptCsITl->AddProperty("RINDEX", energyScint, rindexCsI_Tl, 2);
    mptCsITl->AddProperty("FASTCOMPONENT", energyScint, scintFast, 2);
    mptCsITl->AddProperty("SLOWCOMPONENT", energyScint, scintSlow, 2);
    mptCsITl->AddConstProperty("SCINTILLATIONYIELD", yield);
    mptCsITl->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptCsITl->AddConstProperty("FASTTIMECONSTANT", fastTimeConst);
    mptCsITl->AddConstProperty("SLOWTIMECONSTANT", slowTimeConst);
    mptCsITl->AddConstProperty("YIELDRATIO", 0.8);  // Ratio of fast to slow component

    CsI_Tl->SetMaterialPropertiesTable(mptCsITl);

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // Define the world volume
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 100, true);
    
    // Build the setup
    ConstructSetup();
    
    G4Box *solidDetector = new G4Box("solidDetector", 1.15*mm, 1.15*mm, 5.0*mm);
    LogicDetector = new G4LogicalVolume(solidDetector, Si, "LogicDetector");
    
    for(G4int i = 0; i < 100; i++)
    {
        for(G4int j = 0; j < 100; j++)
        {
            new G4PVPlacement(0, G4ThreeVector(-115.0*mm + (i+0.5)*2.3*mm, -115*mm + (j+0.5)*2.3*mm, 0.21*m), LogicDetector, "physDetector", logicWorld, false, j + i*100, true);
        }
    }
    
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    LogicDetector->SetSensitiveDetector(sensDet);
}


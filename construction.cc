#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  G4NistManager *nist = G4NistManager::Instance();

  // Create material SiO2
  G4Material *SiO2 = new G4Material("SiO2", 2.201 * g / cm3, 2);
  SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
  SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

  // Create material H2O
  G4Material *H2O = new G4Material("H2O", 1.000 * g / cm3, 2);
  H2O->AddElement(nist->FindOrBuildElement("H"), 2);
  H2O->AddElement(nist->FindOrBuildElement("O"), 1);

  // Create element Carbon (C)
  G4Element *C = nist->FindOrBuildElement("C");

  // Create material Aerogel
  G4Material *Aerogel = new G4Material("Aerogel", 0.200 * g / cm3, 3);
  Aerogel->AddMaterial(SiO2, 62.5 * perCent);
  Aerogel->AddMaterial(H2O, 37.4 * perCent);
  Aerogel->AddElement(C, 0.1 * perCent);

  // Define energy and refractive indices
  G4double energy[2] = {1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2};
  G4double rindexAerogel[2] = {1.1, 1.1};
  G4double rindexWorld[2] = {1.0, 1.0};

  // Set material properties for Aerogel
  G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
  mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
  Aerogel->SetMaterialPropertiesTable(mptAerogel);

  // Set material properties for the world material
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
  mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
  worldMat->SetMaterialPropertiesTable(mptWorld);

  // Define the world volume
  G4Box *solidWorld = new G4Box("solidWorld", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(nullptr,                   // No rotation
                        G4ThreeVector(0., 0., 0.), // Position
                        logicWorld,                // Logical volume
                        "physWorld",               // Name
                        nullptr,                   // No mother volume
                        false,                     // No many placement
                        0,                         // Copy number
                        true                       // Check overlaps
      );

  // Define the radiator volume
  G4Box *solidRadiator = new G4Box("solidRadiator", 0.4 * m, 0.4 * m, 0.01 * m);
  G4LogicalVolume *logicRadiator =
      new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
  G4VPhysicalVolume *physRadiator =
      new G4PVPlacement(nullptr,                         // No rotation
                        G4ThreeVector(0., 0., 0.25 * m), // Position
                        logicRadiator,                   // Logical volume
                        "physRadiator",                  // Name
                        logicWorld,                      // Mother volume
                        false,                           // No many placement
                        0,                               // Copy number
                        true                             // Check overlaps
      );

  G4Box *solidDetector =
      new G4Box("solidDetector", 0.005 * m, 0.005 * m, 0.01 * m);

  LogicDetector = new G4LogicalVolume(solidDetector, worldMat, "LogicDetector");

  for (G4int i = 0; i < 100; i++) {
    for (G4int j = 0; j < 100; j++) {
      G4VPhysicalVolume *physDetector = new G4PVPlacement(
          0,
          G4ThreeVector(-0.5 * m + (i + 0.5) * m / 100,
                        -0.5 * m + (j + 0.5) * m / 100, 0.49 * m),
          LogicDetector, "physDetector", logicWorld, false, j + i * 100, true);
    }
  }

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {

  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  LogicDetector->SetSensitiveDetector(sensDet);
}

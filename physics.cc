/*This file is required to integrate the necessary physics like Electromagnetism
 * and Optics*/
#include "physics.hh"

MyPhysicsList::MyPhysicsList()

{
  RegisterPhysics(new G4EmStandardPhysics());
  G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
  opticalPhysics->SetFiniteRiseTime(true); // Enable finite rise time
  RegisterPhysics(opticalPhysics);
  // RegisterPhysics (new G4DecayPhysics());
  // RegisterPhysics (new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList() {}

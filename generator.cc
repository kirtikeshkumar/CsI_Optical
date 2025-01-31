/*In this file we define the particle that we want to generate from the primary
 * generator*/

/*Including the generator header file with all the required classes and
 * functions*/

#include "generator.hh"

/*Constructor and destruction function of the primary generator which creates a
 * new instance of the particle gun and deletes the particle gun respectively.*/

MyPrimaryGenerator::MyPrimaryGenerator() {
  fParticleGun = new G4ParticleGun(1);
}
MyPrimaryGenerator::~MyPrimaryGenerator() { delete fParticleGun; }

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle("proton");

  G4ThreeVector pos(0., 0., 0.);
  G4ThreeVector mom(0., 0., 1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(10. * GeV);
  fParticleGun->SetParticleDefinition(particle);

  // G4ParticleGun* particleGun = new G4ParticleGun();
  // particleGun->SetParticleEnergy(99.0661*GeV);  // Set kinetic energy

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

/*In this file we define the particle that we want to generate from the primary generator*/

/*Including the generator header file with all the required classes and functions*/

#include "generator.hh"
#include <cmath>
 /*Constructor and destruction function of the primary generator which creates a new instance of the particle gun and deletes the particle gun respectively.*/
 
MyPrimaryGenerator::MyPrimaryGenerator()
{
           fParticleGun = new G4ParticleGun(1);
           
    /*Getting the attributes of our particle(proton) from the G4ParticleTable using FindParticle function.*/
 	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 	
 	G4ParticleDefinition *particle = particleTable->FindParticle("e-");
 	
 	/*Defining the position and momentum of the particle using G4ThreeVector to define and SetParticle function to define the properties*/
 	G4ThreeVector pos(0.0, 0.0, 0.15*m);
 	
 	G4ThreeVector mom(0.0, 0.0, 1.0);
 	
 	fParticleGun->SetParticlePosition(pos);
 	fParticleGun->SetParticleMomentumDirection(mom);
 	fParticleGun->SetParticleMomentum(5.0*MeV);
 	fParticleGun->SetParticleEnergy(1.0*MeV);
 	fParticleGun->SetParticleDefinition(particle);        
           
           
           
           
}
MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

fParticleGun->GeneratePrimaryVertex(anEvent);

}

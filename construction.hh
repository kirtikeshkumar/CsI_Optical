/*This is the construction header file where we define the class, variables and functions required for the construction of the environment and the detector*/

//First we include all the necessary header files

#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "detector.hh"


//Here we define the DetectorConstruction class and its variables and functions
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();	


//This is the Construct function of the type G4VPhysicalVolume which is used to construct the detector and environment with the required dimenstions and properties
	virtual G4VPhysicalVolume *Construct();
	
private:
        G4LogicalVolume *LogicDetector;
        virtual void ConstructSDandField();	
	
};



#endif

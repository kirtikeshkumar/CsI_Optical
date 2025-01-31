/*This is the main simulation file*/

/*Including all the required header files*/

#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

// Include your custom detector construction and physics list classes
#include "action.hh"
#include "construction.hh"
#include "physics.hh"

int main(int argc, char **argv) {
  // Create the run manager, responsible for controlling the simulation
  G4RunManager *runManager = new G4RunManager();

  // Initialize the detector construction and physics list
  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  // Initialize the run manager (sets up the geometry and physics)
  runManager->Initialize();

  // Initialize the visualization manager
  // G4VisManager *visManager = new G4VisExecutive();
  // visManager->Initialize();

  // // Get the user interface manager
  // G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // // Set up visualization commands
  // UImanager->ApplyCommand("/control/execute vis.mac");
  // UImanager->ApplyCommand("/vis/open OGL "); // Use Qt-based OpenGL viewer

  G4UIExecutive *ui = 0;

  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if (ui) {
    UImanager->ApplyCommand("/control/execute vis.mac");
    // finally we start the session
    ui->SessionStart();
  } else {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  // Clean up after the UI session ends
  // delete ui;
  // delete visManager;
  // delete runManager;

  return 0;
}

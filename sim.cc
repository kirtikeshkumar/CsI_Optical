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
  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  // Get the user interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Set up visualization commands
  UImanager->ApplyCommand("/vis/open OGL "); // Use Qt-based OpenGL viewer
  UImanager->ApplyCommand(
      "/vis/viewer/set/viewpointVector 1 0 0"); // Adjust camera
  UImanager->ApplyCommand("/vis/drawVolume");   // Draw the detector geometry
  UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true"); // Enable
  // auto-refresh

  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth"); //
  UImanager->ApplyCommand("vis/scene/endOfEventAction accumulate");
  UImanager->ApplyCommand("/vis/scene/create"); // Create the scene

  // Create a UI executive session (for interactive UI if needed)
  G4UIExecutive *ui = new G4UIExecutive(argc, argv);
  // Start the interactive session
  ui->SessionStart();

  // Clean up after the UI session ends
  // delete ui;
  // delete visManager;
  // delete runManager;

  return 0;
}

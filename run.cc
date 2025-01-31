#include "run.hh"

MyRunAction::MyRunAction() {}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *) {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  count = 0;
  man->OpenFile("output.root");

  man->CreateNtuple("Hits", "Hits");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  // man->CreateNtupleDColumn("fX");
  // man->CreateNtupleDColumn("fY");
  // man->CreateNtupleDColumn("fZ");
  man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run *) {

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  G4cout << "count: " << count << G4endl;
  man->Write();
  man->CloseFile();
}

void MyRunAction::AddCount(int n) { count = count + n; }

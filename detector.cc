#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name) {}

MySensitiveDetector::~MySensitiveDetector() {}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep,
                                        G4TouchableHistory *ROhist) {
  G4Track *track = aStep->GetTrack();

  G4String particleName = track->GetParticleDefinition()->GetParticleName();
  // G4cout<<"Particle: "<<particleName<<G4endl;

  if (particleName == "opticalphoton") {
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    G4double energy_Photon = preStepPoint->GetMomentum().mag();
    G4double time_Photon = preStepPoint->GetGlobalTime() / ns;

    G4cout << "Time: " << time_Photon << " Energy: " << energy_Photon << G4endl;

    // G4cout << "Photon position:" <<posPhoton << G4endl;

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    // G4cout << "Copy number:" << copyNo << G4endl;
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    // G4cout << "Detector position: " << posDetector << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    MyRunAction *runAction =
        const_cast<MyRunAction *>(dynamic_cast<const MyRunAction *>(
            G4RunManager::GetRunManager()->GetUserRunAction()));

    runAction->AddCount(1);

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, energy_Photon);
    man->FillNtupleDColumn(2, time_Photon);
    // man->FillNtupleDColumn(1, posDetector[0]);
    // man->FillNtupleDColumn(2, posDetector[1]);
    // man->FillNtupleDColumn(3, posDetector[2]);
    man->AddNtupleRow(0);
  }
}

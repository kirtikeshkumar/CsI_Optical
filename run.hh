#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "g4root_defs.hh"
#include "G4AnalysisManager.hh"

 class MyRunAction : public G4UserRunAction
{ 
 public:
 G4int count;
 void AddCount(int n);
 MyRunAction();
 ~MyRunAction();
 
     virtual void BeginOfRunAction(const G4Run*);
     virtual void EndOfRunAction(const G4Run*);

};
#endif

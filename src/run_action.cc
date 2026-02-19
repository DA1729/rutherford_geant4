#include "run_action.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

run_action::run_action() : G4UserRunAction(), counts(36, 0)
{}

run_action::~run_action()
{}

void run_action::BeginOfRunAction(const G4Run*)
{
  for (G4int i = 0; i < 36; i++) counts[i] = 0;
}

void run_action::EndOfRunAction(const G4Run* run)
{
  G4int nof_events = run->GetNumberOfEvent();
  if (nof_events == 0) return;

  G4cout << "--- run results ---" << G4endl;
  for (G4int i = 0; i < 36; i++) {
    G4cout << "angle: " << i * 10 << " deg, counts: " << counts[i] << G4endl;
  }
}

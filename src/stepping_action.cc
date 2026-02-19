#include "stepping_action.hh"
#include "run_action.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4Alpha.hh"

stepping_action::stepping_action(run_action* ra) : G4UserSteppingAction(), r_action(ra)
{}

stepping_action::~stepping_action()
{}

void stepping_action::UserSteppingAction(const G4Step* step)
{
  // check if track is alpha
  if (step->GetTrack()->GetDefinition() != G4Alpha::Alpha()) return;

  // check if entered detector
  G4StepPoint* pre_step = step->GetPreStepPoint();
  G4StepPoint* post_step = step->GetPostStepPoint();

  if (pre_step->GetStepStatus() == fGeomBoundary) {
    G4VPhysicalVolume* volume = post_step->GetPhysicalVolume();
    if (volume && volume->GetName() == "detector") {
      G4int copy_no = volume->GetCopyNo();
      r_action->add_count(copy_no);
      // stop track once it hits detector
      step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
  }
}

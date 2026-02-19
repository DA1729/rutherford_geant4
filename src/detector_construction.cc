#include "detector_construction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

detector_construction::detector_construction() : G4VUserDetectorConstruction()
{}

detector_construction::~detector_construction()
{}

G4VPhysicalVolume* detector_construction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* gold = nist->FindOrBuildMaterial("G4_Au");

  // world box
  G4Box* world_box = new G4Box("world", 10.0*cm, 10.0*cm, 10.0*cm);
  G4LogicalVolume* world_log = new G4LogicalVolume(world_box, vacuum, "world");
  G4VPhysicalVolume* world_phys = new G4PVPlacement(0, G4ThreeVector(), world_log, "world", 0, false, 0);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  // gold foil target
  G4Box* target_box = new G4Box("target", 0.5*cm, 0.5*cm, 1.0*um);
  G4LogicalVolume* target_log = new G4LogicalVolume(target_box, gold, "target");
  G4VisAttributes* target_vis = new G4VisAttributes(G4Color(1.0, 0.84, 0.0)); // gold color
  target_vis->SetForceSolid(true);
  target_log->SetVisAttributes(target_vis);
  new G4PVPlacement(0, G4ThreeVector(), target_log, "target", world_log, false, 0);

  // detectors
  G4Tubs* detector_tub = new G4Tubs("detector", 0.0, 0.5*cm, 0.05*cm, 0.0, 360.0*deg);
  G4VisAttributes* det_vis = new G4VisAttributes(G4Color(0.5, 0.5, 0.5));
  det_vis->SetForceSolid(true);

  for (G4int i = 0; i < 36; i++) {
    G4double angle = i * 10.0 * deg;
    G4double x = 5.75 * cm * std::sin(angle);
    G4double z = 5.75 * cm * std::cos(angle);
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateY(angle);
    G4LogicalVolume* det_log = new G4LogicalVolume(detector_tub, vacuum, "detector");
    det_log->SetVisAttributes(det_vis);
    new G4PVPlacement(rot, G4ThreeVector(x, 0.0, z), det_log, "detector", world_log, false, i);
  }

  return world_phys;
}

void detector_construction::ConstructSDandField()
{}

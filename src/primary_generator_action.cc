#include "primary_generator_action.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

primary_generator_action::primary_generator_action() : G4VUserPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particle_gun = new G4ParticleGun(n_particle);

  G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
  G4String particle_name;
  G4ParticleDefinition* particle = particle_table->FindParticle(particle_name = "alpha");
  particle_gun->SetParticleDefinition(particle);
  particle_gun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  particle_gun->SetParticleEnergy(5.5*MeV);
}

primary_generator_action::~primary_generator_action()
{
  delete particle_gun;
}

void primary_generator_action::GeneratePrimaries(G4Event* an_event)
{
  // source at 5cm from target (at 0,0,0)
  particle_gun->SetParticlePosition(G4ThreeVector(0., 0., -5.*cm));
  particle_gun->GeneratePrimaryVertex(an_event);
}

#ifndef run_action_hh
#define run_action_hh

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class run_action : public G4UserRunAction
{
  public:
    run_action();
    virtual ~run_action();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void add_count(G4int id) { counts[id]++; }

  private:
    std::vector<G4int> counts;
};

#endif

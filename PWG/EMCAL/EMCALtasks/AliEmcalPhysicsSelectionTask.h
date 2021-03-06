#ifndef ALIEMCALPHYSICSSELECTIONTASK_H
#define ALIEMCALPHYSICSSELECTIONTASK_H

// $Id$

#include "AliPhysicsSelectionTask.h"
#include "AliEmcalPhysicsSelection.h"

class TH1;

class AliEmcalPhysicsSelectionTask : public AliPhysicsSelectionTask {
 public:
  AliEmcalPhysicsSelectionTask();
  AliEmcalPhysicsSelectionTask(const char* opt);
  virtual ~AliEmcalPhysicsSelectionTask() {};

  virtual void   UserExec(const Option_t *opt);
  virtual void   UserCreateOutputObjects();
  virtual void   Terminate(Option_t*);

  Int_t          GetNCalled() const         { return fNCalled;    }
  Int_t          GetNAccepted() const       { return fNAccepted;  }
  void           SetDoWriteHistos(Bool_t b) { fDoWriteHistos = b; }
  void           SelectCollisionCandidates(UInt_t offlineTriggerMask = AliVEvent::kMB) 
                  { static_cast<AliEmcalPhysicsSelection*>(fPhysicsSelection)->SetTriggers(offlineTriggerMask); }

 protected:
  Bool_t         fDoWriteHistos; //=true then write output
  Int_t          fNCalled;       //!how often was the PS called
  Int_t          fNAccepted;     //!how often was the event accepted
  TH1           *fHAcc;          //!acceptance histo
  TH1           *fHEvtTypes;     //!event types histo

 private:
  AliEmcalPhysicsSelectionTask(const AliEmcalPhysicsSelectionTask&);
  AliEmcalPhysicsSelectionTask& operator=(const AliEmcalPhysicsSelectionTask&);

  ClassDef(AliEmcalPhysicsSelectionTask, 2); // Emcal physics selection task
};
#endif

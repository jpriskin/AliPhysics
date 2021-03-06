void filterAOD_V0s()
{
  AliAnalysisManager* mgr = new AliAnalysisManager("NanoAOD Filter", "NanoAOD filter for nanoAOD production");
    
  AliAODInputHandler* iH = new AliAODInputHandler();
  mgr->SetInputEventHandler(iH);

  // Define aod output handler
  AliAODHandler* aodOutputHandler = new AliAODHandler();
  aodOutputHandler->SetOutputFileName("AliAOD.NanoAOD.root");
  mgr->SetOutputEventHandler(aodOutputHandler);
  
  AliAnalysisTaskNanoAODFilter* task = (AliAnalysisTaskNanoAODFilter*) gInterpreter->ExecuteMacro("$ALICE_PHYSICS/PWG/DevNanoAOD/AddTaskNanoAODFilter.C(0, kFALSE)");
  task->AddSetter(new AliNanoAODSimpleSetter);
  
  // Event selection
  AliAnalysisNanoAODEventCuts* evtCuts = new AliAnalysisNanoAODEventCuts;
  // NOTE filter bit set in AliEventCuts automatically

  // Track selection
  AliAnalysisNanoAODTrackCuts* trkCuts = new AliAnalysisNanoAODTrackCuts;
  trkCuts->SetBitMask((1 << 8) | (1 << 9)); // hybrid 2011
  trkCuts->SetMaxEta(0.9);
  trkCuts->SetMinPt(1.0);
  
  // Fields to store
  // event level
  // Note: vertices are kept by default
  task->SetVarListHeader("OfflineTrigger,MagField");
  // track level
  task->SetVarListTrack("pt,theta,phi");

  task->SetTrkCuts(trkCuts);
  task->AddEvtCuts(evtCuts);
  
  // V0s
  task->SaveV0s(kTRUE, new AliAnalysisNanoAODV0Cuts);
  task->SaveCascades(kTRUE, new AliAnalysisNanoAODCascadeCuts);

  mgr->SetDebugLevel(1); // enable debug printouts
  if (!mgr->InitAnalysis()) 
    return;
  mgr->PrintStatus();
  
  // Input files
  TChain * chain = new TChain("aodTree");
  chain->Add("AliAOD.root");

  Printf("Starting Analysis....");
  mgr->StartAnalysis("local", chain, 1000);
}

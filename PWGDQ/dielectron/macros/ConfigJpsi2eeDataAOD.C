
void InitHistograms(AliDielectron *die, Int_t cutDefinition);
void InitCF(AliDielectron* die, Int_t cutDefinition);

void SetupTrackCuts(AliDielectron *die, Int_t cutDefinition);
void SetupPairCuts(AliDielectron *die, Int_t cutDefinition);

TString names=("trackQ+Pt>1GeV+loose_PID;trackQ+Pt>1GeV+tight_PID;trackQ+Pt>.5GeV");
TObjArray *arrNames=names.Tokenize(";");

const Int_t nDie=arrNames->GetEntries();

AliDielectron* ConfigJpsi2ee(Int_t cutDefinition)
{
  //
  // Setup the instance of AliDielectron
  //
  
  // create the actual framework object
  TString name=Form("%02d",cutDefinition);
  if (cutDefinition<arrNames->GetEntriesFast()){
    name=arrNames->At(cutDefinition)->GetName();
  }
  AliDielectron *die =
    new AliDielectron(Form("%s",name.Data()),
                      Form("Track cuts: %s",name.Data()));
  
  // cut setup
  SetupTrackCuts(die,cutDefinition);
  SetupPairCuts(die,cutDefinition);
  
  //
  // histogram setup
  // only if an AliDielectronHistos object is attached to the
  //  dielectron framework the QA histograms will be filled
  //
  InitHistograms(die,cutDefinition);

  // the last definition uses no cuts and only the QA histograms should be filled!
  if (cutDefinition<nDie-1) InitCF(die,cutDefinition);
  
  return die;
}

//______________________________________________________________________________________
void SetupTrackCuts(AliDielectron *die, Int_t cutDefinition)
{
  //
  // Setup the track cuts
  //
  
  

  //QA no CF
  if (cutDefinition==nDie-1) {
    //Pt cut
    AliDielectronVarCuts *pt = new AliDielectronVarCuts("Pt>.5","Pt>.5");
    pt->AddCut(AliDielectronVarManager::kPt,.5,1e30);
    die->GetTrackFilter().AddCuts(pt);
    
    return;
  }

  
  AliDielectronVarCuts *pt = new AliDielectronVarCuts("Pt>1","Pt>1");
  pt->AddCut(AliDielectronVarManager::kPt,1.,1e30);
  pt->AddCut(AliDielectronVarManager::kImpactParZ,-3.,3.);
  pt->AddCut(AliDielectronVarManager::kImpactParXY,-.07,.07);
  die->GetTrackFilter().AddCuts(pt);
  
  //loose PID
  if (cutDefinition==0){
    //ESD pid cuts (TPC nSigma Electrons)
    AliDielectronVarCuts *pid = new AliDielectronVarCuts("TPCpid","TPC nSigma cut |e|<3 pi>2 |P|>2 |K|>2");
    //include
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaEle, -3., 3.);
    //exclude
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaPio, -20., 2., kTRUE);
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaPro, -2., 2., kTRUE);
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaKao, -2., 2., kTRUE);
    die->GetTrackFilter().AddCuts(pid);
  }

  //tight PID
  if (cutDefinition==1){
    //ESD pid cuts (TPC nSigma Electrons)
    AliDielectronVarCuts *pid = new AliDielectronVarCuts("TPCpid","TPC nSigma cut |e|<2 pi>2 |P|>2 |K|>2; |dXY|<200um");
    //include
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaEle, -2., 2.);
    //exclude
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaPio, -2., 2., kTRUE);
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaPro, -2., 2., kTRUE);
    pid->AddCut(AliDielectronVarManager::kTPCnSigmaKao, -2., 2., kTRUE);
    //tighten Impact parameter to 200um
    pid->AddCut(AliDielectronVarManager::kImpactParXY, -0.02, 0.02);
    die->GetTrackFilter().AddCuts(pid);
  }
  
}

//______________________________________________________________________________________
void SetupPairCuts(AliDielectron *die, Int_t cutDefinition)
{
  //
  // Setup the pair cuts
  //
  
  //Invariant mass and rapidity selection
  AliDielectronVarCuts *pairCut=new AliDielectronVarCuts("2<M<4+|Y|<.8","2<M<4 + |Y|<.8");
  pairCut->AddCut(AliDielectronVarManager::kM,2.,4.);
  pairCut->AddCut(AliDielectronVarManager::kY,-0.8,0.8);
}

//______________________________________________________________________________________
void InitHistograms(AliDielectron *die, Int_t cutDefinition)
{
  //
  // Initialise the QA histograms
  //

  //Setup QA histograms
  AliDielectronHistos *histos=
    new AliDielectronHistos(die->GetName(),
                            die->GetTitle());
  
  //Initialise histogram classes
  histos->SetReservedWords("Track;Pair");
  
  //Event class (only for last QA)
  if (cutDefinition==nDie-1) histos->AddClass("Event");
  
  //Track classes, only first event
  for (Int_t i=0; i<2; ++i){
    histos->AddClass(Form("Track_%s",AliDielectron::TrackClassName(i)));
  }
  
  //Pair classes, only first event
  for (Int_t i=0; i<3; ++i){
    histos->AddClass(Form("Pair_%s",AliDielectron::PairClassName(i)));
  }

  //Event histograms
  if (cutDefinition==nDie-1){
    //add histograms to event class
    histos->UserHistogram("Event","nEvents","Number of processed events after cuts;Number events",
                          1,0.,1.,AliDielectronVarManager::kNevents);
  }
  
  //add histograms to Track classes
  histos->UserHistogram("Track","Pt","Pt;Pt [GeV];#tracks",200,0,20.,AliDielectronVarManager::kPt);
  histos->UserHistogram("Track","dEdx_P","dEdx;P [GeV];TPC signal (arb units);#tracks",
                        400,0.2,20.,200,0.,200.,AliDielectronVarManager::kPIn,AliDielectronVarManager::kTPCsignal,kTRUE);
  histos->UserHistogram("Track","TPCnSigmaEle_P","TPC number of sigmas Electrons;P [GeV];TPC number of sigmas Electrons;#tracks",
                        400,0.2,20.,100,-5.,5.,AliDielectronVarManager::kPIn,AliDielectronVarManager::kTPCnSigmaEle,kTRUE);
  histos->UserHistogram("Track","TPCnSigmaPio_P","TPC number of sigmas Pions;P [GeV];TPC number of sigmas Pions;#tracks",
                        400,0.2,20.,100,-5.,5.,AliDielectronVarManager::kPIn,AliDielectronVarManager::kTPCnSigmaPio,kTRUE);
  histos->UserHistogram("Track","dXY","dXY;dXY [cm];#tracks",200,-2.,2.,AliDielectronVarManager::kImpactParXY);
  
  //add histograms to Pair classes
  histos->UserHistogram("Pair","InvMass","Inv.Mass;Inv. Mass [GeV];#pairs",
                        500,0.,4.,AliDielectronVarManager::kM);
  histos->UserHistogram("Pair","Rapidity","Rapidity;Rapidity;#pairs",
                        100,-2.,2.,AliDielectronVarManager::kY);
  histos->UserHistogram("Pair","OpeningAngle","Opening angle;angle",
                        100,0.,3.15,AliDielectronVarManager::kOpeningAngle);
  histos->UserHistogram("Pair","Chi2/NDF","#Chi^{2}/NDF;#Chi^{2}/NDF",
                        100, 0., 20., AliDielectronVarManager::kChi2NDF);
  
  die->SetHistogramManager(histos);
}


void InitCF(AliDielectron* die, Int_t cutDefinition)
{
  //
  // Setupd the CF Manager if needed
  //
  AliDielectronCF *cf=new AliDielectronCF(die->GetName(),die->GetTitle());
  
  //pair variables
  cf->AddVariable(AliDielectronVarManager::kPt,20,0,10);
  cf->AddVariable(AliDielectronVarManager::kY,40,-2,2);
  cf->AddVariable(AliDielectronVarManager::kM,200,-0.01,3.99);
  cf->AddVariable(AliDielectronVarManager::kPairType,10,0,10);
  //leg variables
  cf->AddVariable(AliDielectronVarManager::kPt,20,0,10,kTRUE);
  
  //only in this case write MC truth info
  cf->SetStepsForCutsIncreasing();
  if (cutDefinition==0){
    cf->SetStepForMCtruth();
  }
  
  die->SetCFManagerPair(cf);
}

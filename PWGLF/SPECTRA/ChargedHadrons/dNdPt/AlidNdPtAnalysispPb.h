#ifndef ALIDNDPTANALYSISPPB_H
#define ALIDNDPTANALYSISPPB_H

//------------------------------------------------------------------------------
// AlidNdPtAnalysispPb class used for dNdPt analysis in p-Pb collisions
// based on AlidNdPtAnalysis class
//
// Author: J.Otwinowski 04/11/2008
// last change: 2013-06-19 by M.Knichel
//------------------------------------------------------------------------------

class iostream;

class TFile;
class TCint;
class TProfile;
class TFolder;
class TObjArray;
class TString;
class THnSparse;

class AliESDtrackCuts;
class AliVertexerTracks;
class AliESD;
class AliESDfriend;
class AliESDfriendTrack;
class AlidNdPtHelper;
class AliAnalysisUtils;
class AliTRDTriggerAnalysis;
class AliESDVertex;
class AliTRDSensorArray;

#include "AlidNdPt.h"
#include "TObjString.h"

class AlidNdPtAnalysispPb : public AlidNdPt {
public :
  AlidNdPtAnalysispPb();
  AlidNdPtAnalysispPb(Char_t* name, Char_t* title);
  ~AlidNdPtAnalysispPb();

  // Init data members
  virtual void Init();

  // Process events
  virtual void Process(AliESDEvent *const esdEvent=0, AliMCEvent *const mcEvent=0);

  // Merge output objects (needed by PROOF)
  virtual Long64_t Merge(TCollection* const list);

  // Analyse output histograms
  virtual void Analyse();

  // Export objects to folder
  virtual TFolder *ExportToFolder(TObjArray * const array=0);

  // Get analysis folder
  TFolder* GetAnalysisFolder() const {return fAnalysisFolder;}

  // Fill control histograms
  void SetHistogramsOn(Bool_t histOn=kTRUE) {fHistogramsOn = histOn;}
  Bool_t IsHistogramsOn() const {return fHistogramsOn;}

  // Define 0-multiplicity bin for LHC
  // background calculation
  static Bool_t IsBinZeroSPDvtx(const AliESDEvent* esdEvent);
  static Bool_t IsBinZeroTrackSPDvtx(const AliESDEvent* esdEvent);

  // Create folder for analysed histograms
  TFolder *CreateFolder(TString folder = "folderdNdPtAnalysis",TString title = "Analysed dNdPt histograms");

  // Set binning for Histograms (if not set default binning is used)
  void SetBinsMult(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fMultNbins = nbins; fBinsMult = CloneArray(fMultNedges = nbins+1,edges); } }
  void SetBinsMultTE(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fMultNbinsTE = nbins; fBinsMultTE = CloneArray(fMultNedgesTE = nbins+1,edges); } }
  void SetBinsPt(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fPtNbins = nbins; fBinsPt = CloneArray(fPtNedges = nbins+1,edges); } }
  void SetBinsPtCorr(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fPtCorrNbins = nbins; fBinsPtCorr = CloneArray(fPtCorrNedges = nbins+1,edges); } }
  void SetBinsEta(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fEtaNbins = nbins; fBinsEta = CloneArray(fEtaNedges = nbins+1,edges); } }
  void SetBinsZv(Int_t nbins, Double_t* edges) { if (CanChangeBins()) {  fZvNbins = nbins; fBinsZv = CloneArray(fZvNedges = nbins+1,edges); } }

  void SetTRDTriggerHQU(const Bool_t require = kFALSE) { fTRDTriggerRequiredHQU = require;}
  void SetTRDTriggerHJT(const Bool_t require = kFALSE) { fTRDTriggerRequiredHJT = require;}
  void SetTRDTriggerHSE(const Bool_t require = kFALSE) { fTRDTriggerRequiredHSE = require;}
  
  
  // Fill histograms
  void FillHistograms(AliESDtrack *const esdTrack, AliStack *const stack, const Double_t zv, AlidNdPtHelper::TrackObject trackObj, Int_t multMB);
  void FillHistograms(AliStack *const stack, Int_t label, AlidNdPtHelper::TrackObject trackObj);
  void FillHistograms(TObjArray *const allChargedTracks,Int_t *const labelsAll,Int_t multAll,Int_t *const labelsAcc,Int_t multAcc,Int_t *const labelsRec,Int_t multRec);

  // Getters
  THnSparseF *GetEventMultCorrelationMatrix() const {return fEventMultCorrelationMatrix;}
  THnSparseF *GetTrackPtCorrelationMatrix()   const {return fTrackPtCorrelationMatrix;}


  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  //kNSD would have to be added to PWG0Helper, now kND is used to signal NSD!
  THnSparseF *GetGenEventMatrix() const {return fGenEventMatrix;}
  THnSparseF *GetGenSDEventMatrix() const {return fGenSDEventMatrix;}
  THnSparseF *GetGenDDEventMatrix() const {return fGenDDEventMatrix;}
  THnSparseF *GetGenNDEventMatrix() const {return fGenNDEventMatrix;}
  THnSparseF *GetGenNSDEventMatrix() const {return fGenNSDEventMatrix;}

  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  THnSparseF *GetTriggerEventMatrix() const {return fTriggerEventMatrix;}
  THnSparseF *GetTriggerSDEventMatrix() const {return fTriggerSDEventMatrix;}
  THnSparseF *GetTriggerDDEventMatrix() const {return fTriggerDDEventMatrix;}
  THnSparseF *GetTriggerNDEventMatrix() const {return fTriggerNDEventMatrix;}
  THnSparseF *GetTriggerNSDEventMatrix() const {return fTriggerNSDEventMatrix;}

  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  THnSparseF *GetRecEventMatrix() const {return fRecEventMatrix;}
  THnSparseF *GetRecSDEventMatrix() const {return fRecSDEventMatrix;}
  THnSparseF *GetRecDDEventMatrix() const {return fRecDDEventMatrix;}
  THnSparseF *GetRecNDEventMatrix() const {return fRecNDEventMatrix;}
  THnSparseF *GetRecNSDEventMatrix() const {return fRecNSDEventMatrix;}

  //
  THnSparseF *GetRecCandleEventMatrix() const {return fRecCandleEventMatrix;}

  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  THnSparseF *GetGenTrackEventMatrix() const {return fGenTrackEventMatrix;}
  THnSparseF *GetGenTrackSDEventMatrix() const {return fGenTrackSDEventMatrix;}
  THnSparseF *GetGenTrackDDEventMatrix() const {return fGenTrackDDEventMatrix;}
  THnSparseF *GetGenTrackNDEventMatrix() const {return fGenTrackNDEventMatrix;}
  THnSparseF *GetGenTrackNSDEventMatrix() const {return fGenTrackNSDEventMatrix;}

  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  THnSparseF *GetTriggerTrackEventMatrix() const {return fTriggerTrackEventMatrix;}
  THnSparseF *GetTriggerTrackSDEventMatrix() const {return fTriggerTrackSDEventMatrix;}
  THnSparseF *GetTriggerTrackDDEventMatrix() const {return fTriggerTrackDDEventMatrix;}
  THnSparseF *GetTriggerTrackNDEventMatrix() const {return fTriggerTrackNDEventMatrix;}
  THnSparseF *GetTriggerTrackNSDEventMatrix() const {return fTriggerTrackNSDEventMatrix;}

  //NOTE: for now in p-Pb ND and NSD are the same, DD is empty!
  THnSparseF *GetRecTrackEventMatrix() const {return fRecTrackEventMatrix;}
  THnSparseF *GetRecTrackSDEventMatrix() const {return fRecTrackSDEventMatrix;}
  THnSparseF *GetRecTrackDDEventMatrix() const {return fRecTrackDDEventMatrix;}
  THnSparseF *GetRecTrackNDEventMatrix() const {return fRecTrackNDEventMatrix;}
  THnSparseF *GetRecTrackNSDEventMatrix() const {return fRecTrackNSDEventMatrix;}

  //
  THnSparseF *GetGenTrackMatrix() const {return fGenTrackMatrix;}
  THnSparseF *GetGenPrimTrackMatrix() const {return fGenPrimTrackMatrix;}
  THnSparseF *GetRecPrimTrackMatrix() const {return fRecPrimTrackMatrix;}

  THnSparseF *GetRecTrackMatrix() const {return fRecTrackMatrix;}
  THnSparseF *GetRecSecTrackMatrix() const {return fRecSecTrackMatrix;}
  THnSparseF *GetRecMultTrackMatrix() const {return fRecMultTrackMatrix;}

  //
  // control histograms
  //
  THnSparseF *GetMCEventHist1() const {return fMCEventHist1;}
  THnSparseF *GetRecEventHist1() const {return fRecEventHist1;}
  THnSparseF *GetRecEventHist2() const {return fRecEventHist2;}
  THnSparseF *GetRecMCEventHist1() const {return fRecMCEventHist1;}
  THnSparseF *GetRecMCEventHist2() const {return fRecMCEventHist2;}
  THnSparseF *GetRecMCEventHist3() const {return fRecMCEventHist3;}

  THnSparseF *GetMCTrackHist1(Int_t i) const {return fMCTrackHist1[i];}
  THnSparseF *GetMCPrimTrackHist1(Int_t i) const {return fMCPrimTrackHist1[i];}
  THnSparseF *GetMCPrimTrackHist2(Int_t i) const {return fMCPrimTrackHist2[i];}
  THnSparseF *GetMCSecTrackHist1(Int_t i) const {return fMCSecTrackHist1[i];}

  THnSparseF *GetRecTrackHist1(Int_t i) const {return fRecTrackHist1[i];}
  THnSparseF *GetRecTrackMultHist1(Int_t i) const {return fRecTrackMultHist1[i];}

  THnSparseF *GetRecMCTrackHist1() const {return fRecMCTrackHist1;}
  THnSparseF *GetMCMultRecTrackHist1() const {return fMCMultRecTrackHist1;}

  THnSparseF *GetRecTrackHist2() const {return fRecTrackHist2;}
  THnSparseF *GetEventCount() const {return fEventCount;}

  //
  // Generic histograms to be corrected
  //
  THnSparseF* GetRecEventHist() const {return fRecEventHist;}
  THnSparseF* GetRecTrackHist() const {return fRecTrackHist;}
  THnSparseF* GetEventMultHist() const {return fEventMultHist;}
  THnSparseF* GetMCPrimTrackHist() const {return fMCPrimTrackHist;}

  //
  // centrality histograms etc. getter+setter
  //
  THnSparseF* GetCentralityEventHist() const {return fCentralityEventHist;}
  THnSparseF* GetCentralityTrackHist() const {return fCentralityTrackHist;}
  const char* GetCentralityEstimator(Int_t i) {return ((i > 0) && (i <= fDimensionsCentralityEstimators)) ? ((TObjString*)fCentralityEstimatorsList->At(i-1))->GetName() : 0; }
  Int_t GetNCentralityEstimators() {return fDimensionsCentralityEstimators;}
  void SetBinsCentrality(Int_t nbins, Double_t* edges) { if (CanChangeBins()) { fCentralityNbins = nbins; fBinsCentrality = CloneArray(fCentralityNedges = nbins+1,edges); } }
  void SetCentralityEstimators(const char* estimators);

  //rapidity shift getter+setter
  void SetRapidityShift(Double_t yShift) { fRapidityShift = yShift;}
  Double_t GetRapidityShift() { return fRapidityShift; }

  void Set2013pA(Bool_t is2013 = kTRUE) { fIs2013pA = is2013; }
  Double_t Get2013pA() { return fIs2013pA; }


private:

  // analysis folder
  TFolder *fAnalysisFolder; // folder for analysed histograms
  Bool_t fHistogramsOn; // switch on/off filling of control histograms

  //
  // correlation matrices (histograms)
  //

  // event rec. track vs true track multiplicity correlation matrix
  THnSparseF *fEventMultCorrelationMatrix; //-> multRecMult:multTrueMC:multMB

  // rec. track pt vs true track pt correlation matrix for given eta
  THnSparseF *fTrackPtCorrelationMatrix; //-> Pt:mcPt:mcEta

  //
  // event level correction
  //

  // all genertated
  THnSparseF *fGenEventMatrix; //-> mcZv:multTrueMC (inelastic)
  THnSparseF *fGenSDEventMatrix; //-> mcZv:multTrueMC (single diffractive)
  THnSparseF *fGenDDEventMatrix; //-> mcZv:multTrueMC (single diffractive)
  THnSparseF *fGenNDEventMatrix; //-> mcZv:multTrueMC (non diffractive)
  THnSparseF *fGenNSDEventMatrix; //-> mcZv:multTrueMC (non single diffractive)

  // trigger bias corrections (fTriggerEventMatrix / fGenEventMatrix)
  THnSparseF *fTriggerEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fTriggerSDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fTriggerDDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fTriggerNDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fTriggerNSDEventMatrix; //-> mcZv:multTrueMC

  // event vertex rec. eff correction (fRecEventMatrix / fTriggerEventMatrix)
  THnSparseF *fRecEventMatrix; //-> mcZv:multTrueMC:Centrality
  THnSparseF *fRecSDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fRecDDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fRecNDEventMatrix; //-> mcZv:multTrueMC
  THnSparseF *fRecNSDEventMatrix; //-> mcZv:multTrueMC

  //
  // track-event level correction
  //

  THnSparseF *fGenTrackEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fGenTrackSDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fGenTrackDDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fGenTrackNDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fGenTrackNSDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC

  // trigger bias corrections (fTriggerTrackEventMatrix / fGenTrackEventMatrix)
  THnSparseF *fTriggerTrackEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fTriggerTrackSDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fTriggerTrackDDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fTriggerTrackNDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC
  THnSparseF *fTriggerTrackNSDEventMatrix; //-> mcZv:mcPt:mcEta:multTrueMC

  // event vertex rec. corrections (fRecTrackEventMatrix / fTriggerTrackEventMatrix)
  THnSparseF *fRecTrackEventMatrix; //-> mcZv:Pt:mcEta:multTrueMC
  THnSparseF *fRecTrackSDEventMatrix; //-> mcZv:Pt:mcEta:multTrueMC
  THnSparseF *fRecTrackDDEventMatrix; //-> mcZv:Pt:mcEta:multTrueMC
  THnSparseF *fRecTrackNDEventMatrix; //-> mcZv:Pt:mcEta:multTrueMC
  THnSparseF *fRecTrackNSDEventMatrix; //-> mcZv:Pt:mcEta:multTrueMC

  //
  // track level correction
  //

  // track rec. efficiency correction (fRecPrimTrackMatrix / fGenPrimTrackMatrix)
  THnSparseF *fGenTrackMatrix; //-> mcZv:mcPt:mcEta
  THnSparseF *fGenPrimTrackMatrix; //-> mcZv:mcPt:mcEta:Centrality
  THnSparseF *fRecPrimTrackMatrix; //-> mcZv:mcPt:mcEta:Centrality

  // secondary track contamination correction (fRecSecTrackMatrix / fRecTrackMatrix)
  THnSparseF *fRecTrackMatrix;    //-> mcZv:mcPt:mcEta:Centrality
  THnSparseF *fRecSecTrackMatrix; //-> mcZv:mcPt:mcEta:Centrality

  // multiple rec. track corrections (fRecMultTrackMatrix / fRecTrackMatrix)
  THnSparseF *fRecMultTrackMatrix; //-> mcZv:Pt:mcEta

  //
  // ESD and MC control analysis histograms
  //

  // THnSparse event histograms
  THnSparseF *fMCEventHist1;  //-> mcXv:mcYv:mcZv
  THnSparseF *fRecEventHist1; //-> Xv:Yv:Zv
  THnSparseF *fRecEventHist2; //-> Zv:multMB:multRecMult
  THnSparseF *fRecMCEventHist1; //-> Xv-mcXv:Yv-mcYv:Zv-mcZv
  THnSparseF *fRecMCEventHist2; //-> Xv-mcXv:Zv-mcZv:multMB
  THnSparseF *fRecMCEventHist3; //-> multRec:EventType (ND, DD, SD)

  // THnSparse track histograms
  // [0] - after charged track selection, [1] - after acceptance cuts, [2] - after esd track cuts

  THnSparseF *fMCTrackHist1[AlidNdPtHelper::kCutSteps];     //-> mcPt:mcEta:mcPhi
  THnSparseF *fMCPrimTrackHist1[AlidNdPtHelper::kCutSteps]; //-> mcPt:mcEta:pid:mech:mother
  THnSparseF *fMCPrimTrackHist2[AlidNdPtHelper::kCutSteps]; //-> pdg:mech:mother
  THnSparseF *fMCSecTrackHist1[AlidNdPtHelper::kCutSteps];  //-> mcPt:mcEta:pid:mech:mother

  THnSparseF *fRecTrackHist1[AlidNdPtHelper::kCutSteps];     //-> Pt:Eta:Phi
  THnSparseF *fRecTrackMultHist1[AlidNdPtHelper::kCutSteps]; //-> Pt:mult

  THnSparseF *fRecMCTrackHist1; //-> mcPt:mcEta:(Pt-mcPt)/mcPt:(Eta-mcEta)

  //multple reconstructed tracks
  THnSparseF *fMCMultRecTrackHist1; //-> mcPt:mcEta:pid

  // track control histograms
  THnSparseF *fRecTrackHist2;  //-> nclust:chi2:Pt:Eta:Phi

  //
  // Generic histograms to be corrected
  //
  THnSparseF *fRecEventHist;    //-> Zv:multMB
  THnSparseF *fRecTrackHist; //-> Zv:pT:eta:multRecMult
  THnSparseF *fEventCount; //-> trig, trig + vertex, selected event
  THnSparseF *fEventMultHist; // event multiplicities multMB:multRecMult:multRec
  THnSparseF *fMCPrimTrackHist; //-> Zv:mcpT:mceta:multTrueMC

  //
  // candle events track corrections
  //
  THnSparseF *fRecCandleEventMatrix; // Zv:multMB

  // centrality test histograms
  THnSparseF *fCentralityEventHist; // rec event hist with centrality zv:multRecMult:multMB:cent:...
  THnSparseF *fCentralityTrackHist; // rec track hist with centrality zv:pt:eta:multRecMult:multMB:cent:...
  TObjArray *fCentralityEstimatorsList; // TObjArray with TObjStrings containing cent. estimators
  Int_t fDimensionsCentralityEstimators;  // number of centrality estimators: if 0 hists are not filled
  Int_t fCentralityNbins;  // number of centrality bins (common for all estimators)
  Int_t fCentralityNedges; // fCentralityNbins+1 uses for streaming dynamic array
  Double_t *fBinsCentrality; //[fCentralityNedges]

  Int_t fNVCentralityEvent; //
  Int_t fNVCentralityTrack; //
  Double_t *fVCentralityEvent; //[fNVCentralityEvent]
  Double_t *fVCentralityTrack; //[fNVCentralityTrack]

  //binning for THNsparse
  Int_t fMultNbins;
  Int_t fMultNbinsTE;
  Int_t fPtNbins;
  Int_t fPtCorrNbins;
  Int_t fEtaNbins;
  Int_t fZvNbins;
  Int_t fMultNedges;   // fMultNbins+1 uses for streaming dynamic array
  Int_t fMultNedgesTE; // fMultNbinsTE+1 uses for streaming dynamic array
  Int_t fPtNedges;     // fPtNbins+1 uses for streaming dynamic array
  Int_t fPtCorrNedges; // fCentralityNbins+1 uses for streaming dynamic array
  Int_t fEtaNedges;    // fEtaNbins+1 uses for streaming dynamic array
  Int_t fZvNedges;     // fZvNbins+1 uses for streaming dynamic array
  Double_t *fBinsMult;   //[fMultNedges]
  Double_t *fBinsMultTE; //[fMultNedgesTE]
  Double_t *fBinsPt;     //[fPtNedges]
  Double_t *fBinsPtCorr; //[fPtCorrNedges]
  Double_t *fBinsEta;    //[fEtaNedges]
  Double_t *fBinsZv;     //[fZvNedges]

  Double_t fRapidityShift; //y shift CMS vs. LAB
  AliAnalysisUtils* fUtils;
  Bool_t fIs2013pA;

  Bool_t fIsInit;
  
  Bool_t fTRDTriggerRequiredHQU;
  Bool_t fTRDTriggerRequiredHJT;
  Bool_t fTRDTriggerRequiredHSE;
  Bool_t triggerResult;
  
  // generic function to change binning
  Bool_t CanChangeBins();

  AlidNdPtAnalysispPb(const AlidNdPtAnalysispPb&); // not implemented
  AlidNdPtAnalysispPb& operator=(const AlidNdPtAnalysispPb&); // not implemented

  ClassDef(AlidNdPtAnalysispPb,6);
};

#endif

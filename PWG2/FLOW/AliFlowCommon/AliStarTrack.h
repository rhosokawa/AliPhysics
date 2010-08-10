/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
* See cxx source for full Copyright notice */
/* $Id$ */

/*****************************************************************
  AliStarTrack: Track container for a star track
                                     
  origin:   Mikolaj Krzewicki  (mikolaj.krzewicki@cern.ch)
*****************************************************************/

#ifndef ALISTARTRACK_H
#define ALISTARTRACK_H

#include <TObject.h>

class AliStarTrack : public TObject {

 private:
  static const Int_t fgkNparams = 15; //number of params
  Float_t fParams[fgkNparams]; //params

 public:
  AliStarTrack();
  AliStarTrack( const Float_t* params );
  AliStarTrack( const AliStarTrack& track );
  AliStarTrack& operator=( const AliStarTrack& track );
  virtual ~AliStarTrack() {}
  virtual AliStarTrack* Clone( const char* option="" ) const;
  virtual void Print( Option_t* option = "" ) const;

  const Int_t GetID() const {return (Int_t)fParams[0];}
  const Int_t GetCharge() const {return (Int_t)fParams[1];}
  const Float_t GetEta() const {return fParams[2];}
  const Float_t GetPhi() const {return fParams[3];}
  const Float_t GetPt() const {return fParams[4];}
  const Float_t GetDCA() const {return fParams[5];}
  const Int_t GetNHits() const {return (Int_t)fParams[6];}
  const Int_t GetNHitsFit() const {return (Int_t)fParams[7];}
  const Int_t GetNHitsPoss() const {return (Int_t)fParams[8];}
  const Int_t GetNHitsDedx() const {return (Int_t)fParams[9];}
  const Float_t GetdEdx() const {return fParams[10];}
  const Float_t GetNSigElect() const {return fParams[11];}
  const Float_t GetNSigPi() const {return fParams[12];}
  const Float_t GetNSigK() const {return fParams[13];}
  const Float_t GetNSigProton() const {return fParams[14];}
  const Float_t* GetParams() const {return fParams;}

  void SetID( const Int_t p)  { fParams[0]=(Float_t)p;}
  void SetCharge( const Int_t p)  { fParams[1]=(Float_t)p;}
  void SetEta( const Float_t p)  { fParams[2]=p;}
  void SetPhi( const Float_t p)  { fParams[3]=p;}
  void SetPt( const Float_t p)  { fParams[4]=p;}
  void SetDCA( const Float_t p)  { fParams[5]=p;}
  void SetNHits( const Int_t p)  { fParams[6]=(Float_t)p;}
  void SetNHitsFit( const Int_t p)  { fParams[7]=(Float_t)p;}
  void SetNHitsPoss( const Int_t p)  { fParams[8]=(Float_t)p;}
  void SetNHitsDedx( const Int_t p)  { fParams[9]=(Float_t)p;}
  void SetdEdx( const Float_t p)  { fParams[10]=p;}
  void SetNSigElect( const Float_t p)  { fParams[11]=p;}
  void SetNSigPi( const Float_t p)  { fParams[12]=p;}
  void SetNSigK( const Float_t p)  { fParams[13]=p;}
  void SetNSigProton( const Float_t p)  { fParams[14]=p;}
  void SetParams( const Float_t* params );

  ClassDef(AliStarTrack,1)         // Base class

};

#endif


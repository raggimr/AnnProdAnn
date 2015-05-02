#ifndef Histo_h
#define Histo_h

#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TList.h>
#include "Param.h"
class Histo {
public :
  //  Histo();
  ~Histo();
  static Histo* GetInstance();
  
  void WriteHisto();
  TH1D* Get1DHisto(const char* name){return (TH1D*)hListGen->FindObject(name);}; 
  TH2D* Get2DHisto(const char* name){return (TH2D*)hListGen->FindObject(name);};
  TGraphErrors* GetGraph(const char* name){return (TGraphErrors*)hListGen->FindObject(name);};

 private:
  void InitHisto();
 private:
  Param* par;

  TList* hListGen;  
  TH1D* hNTracks; 
  TH1D* hETracks;

  TH1D* hNTracksRec; 
  TH1D* hETracksRec;
  TH1D* hEtotVis;
 
  TH1D* hNCluster;
  TH1D* hNPosVeto;
  TH1D* hEPosVeto;
  TH1D* hNSAC;   
  TH1D* hNSACCut; 

  TH2D* hClusterMap; 
  TH2D* hClusterEvsR; 
  TH2D* hClEvsMM2; 
  TH1D* hClusterE;  
  TH1D* hClusterRad;
  TH1D* hDtTrkCl;
  TH1D* hDtSACCl;
  TH1D* hDtVetoCl;
  TH1D* hM2Miss;
  TH1D* hM2MissVeto;

  TH1D* hM2Miss3g;
  TH1D* hM2Miss3gSAC;

  TH1D* hESAC3g;   
  TH1D* hESAC3gSAC;

  TH1D* hGGMass;
  TH1D* hAccVisEtrk;

  TH1D* hAccM2Miss;  
  TH1D* hAccClusterE;

  TH2D ** hInvThEi;
  TH2D ** hAccThEi;
  TH1D ** hInvEiTrk;
  TH1D ** hInvMMiss2i;
  TH2D ** hAccClEvsMM2;   

  static Histo* fInstance;
  
 protected:
  Histo();
  
};
#endif

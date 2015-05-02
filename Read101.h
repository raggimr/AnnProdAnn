//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jan  9 16:06:43 2015 by ROOT version 5.28/00
// from TTree U101/Envent
// found on file: UBTF.root
//////////////////////////////////////////////////////////

#ifndef Read101_h
#define Read101_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Histo.h"
#include "CompT0.h"
#include "Param.h"

class Read101 {
 private:
  Long64_t fNentries;
  Long64_t fJentry;
  Long64_t fNbytes;

  Histo* his;
  Param* par;
  CompT0* T0;
 
 public:
  double DtTrkCl[100];
  double DtVetoCl[100];
  double DtSACCl[100];
 private:
  int NBGMass[20];
  int NBGMassVis[20];

  int NBG3gMass[20];
  int NBG3gMassVis[20];

  int InTimeTrkInd[20];
 public:
  int GetNBG(int massa){return NBGMass[massa];};
  int GetNBGVis(int massa){return NBGMassVis[massa];};
  int GetNBG3g(int massa){return NBG3gMass[massa];};
  int GetNBG3gVis(int massa){return NBG3gMassVis[massa];};

  int ZeroNBG(){for(int ll=0;ll<20;ll++) NBGMass[ll]=0.;};
  int ZeroNBGVis(){for(int ll=0;ll<20;ll++) NBGMassVis[ll]=0.;};
  int ZeroNBG3g(){for(int ll=0;ll<20;ll++) NBG3gMass[ll]=0.;};
  int ZeroNBG3gVis(){for(int ll=0;ll<20;ll++) NBG3gMassVis[ll]=0.;};

 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  Histo          *fHisto;   //Pointer to the Histogram class 
  Param          *fParam;   //Pointer to the Param class 
  
  Read101(TTree *tree=0);
  ~Read101();
  Int_t    Cut(Long64_t entry);
  Int_t    GetEntry(Long64_t entry);
  Int_t    IsTrkInTime(int IClus, double win);
  Int_t    IsVetoInTime(int IClus, double win);
  Int_t    IsSACInTime(int IClus, double win);
  Long64_t LoadTree(Long64_t entry);
  void     Init(TTree *tree);
  void     Loop();
  Long64_t LoopInit();
  Long64_t LoopNext();
  Bool_t   Notify();
  void     Show(Long64_t entry = -1);
  Int_t SelectVis(Int_t Doplot, Int_t nacc);
  Int_t SelectInv(Int_t Doplot, Int_t nacc);
  Int_t SelectAnn();
  Double_t GGMass();
  
  // Declaration of leaf types
  Int_t           Nevent;
  Double_t        ETot;
  Double_t        IDProc;
  Double_t        PBeam;
  Double_t        XBeam;
  Double_t        YBeam;
  Int_t           NClusters;
  Int_t           NTracks;
  Int_t           NVetoTracks;
  Int_t           NSAC;
  Int_t           NTarget;
  Double_t        ESAC[100];
  Double_t        TSAC[100];
  Double_t        PTypeSAC[100];
  Double_t        ECluster[20];
  Double_t        QCluster[20];
  Double_t        XCluster[20];
  Double_t        YCluster[20];
  Double_t        ThCluster[20];
  Double_t        M2Cluster[20];
  Double_t        TCluster[20];
  Double_t        ECell[1000];
  Double_t        QCell[1000];
  Double_t        ETracker[100];
  Double_t        TrackerLay[100];
  Double_t        TTracker[100];
  Double_t        ZTracker[100];
  Double_t        XTracker[100];
  Double_t        YTracker[100];
  Double_t        ETarget;
  Double_t        TTarget;
  Double_t        XTarget;
  Double_t        YTarget;
  Double_t        VetoTrEne[100];
  Int_t           VetoNFing[100];
  Double_t        VetoTrTime[100];
  Double_t        VetoFingE[100];
  Double_t        VetoY[100];
  Double_t        VetoX[100];
  
  // List of branches
  TBranch        *b_Nevent;   //!
  TBranch        *b_ETot;   //!
  TBranch        *b_IDProc;   //!
  TBranch        *b_PBeam;   //!
  TBranch        *b_XBeam;   //!
  TBranch        *b_YBeam;   //!
  TBranch        *b_NClusters;   //!
  TBranch        *b_NTracks;   //!
  TBranch        *b_NVetoTracks;   //!
  TBranch        *b_NSAC;   //!
  TBranch        *b_NTarget;   //!
  TBranch        *b_ESAC;   //!
  TBranch        *b_TSAC;   //!
  TBranch        *b_PTypeSAC;   //!
  TBranch        *b_ECluster;   //!
  TBranch        *b_QCluster;   //!
  TBranch        *b_XCluster;   //!
  TBranch        *b_YCluster;   //!
  TBranch        *b_ThCluster;   //!
  TBranch        *b_M2Cluster;   //!
  TBranch        *b_TCluster;   //!
  TBranch        *b_ECell;   //!
  TBranch        *b_QCell;   //!
  TBranch        *b_ETracker;   //!
  TBranch        *b_TrackerLay;   //!
  TBranch        *b_TTracker;   //!
  TBranch        *b_ZTracker;   //!
  TBranch        *b_XTracker;   //!
  TBranch        *b_YTracker;   //!
  TBranch        *b_ETarget;   //!
  TBranch        *b_TTarget;   //!
  TBranch        *b_XTarget;   //!
  TBranch        *b_YTarget;   //!
  TBranch        *b_NTVetoTrkEne;   //!
  TBranch        *b_NTVetoTrkFinger;   //!
  TBranch        *b_NTVetoTrkTime;   //!
  TBranch        *b_NTVetoFingE;   //!
  TBranch        *b_NTVetoX;   //!
  TBranch        *b_NTVetoY;   //!
};
#endif

#ifdef Read101_cxx

Read101::~Read101()
{
  //   if (!fChain) return;
  //   delete fChain->GetCurrentFile();
}

Int_t Read101::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Read101::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Read101::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Nevent", &Nevent, &b_Nevent);
   fChain->SetBranchAddress("ETot", &ETot, &b_ETot);
   fChain->SetBranchAddress("IDProc", &IDProc, &b_IDProc);
   fChain->SetBranchAddress("PBeam", &PBeam, &b_PBeam);
   fChain->SetBranchAddress("XBeam", &XBeam, &b_XBeam);
   fChain->SetBranchAddress("YBeam", &YBeam, &b_YBeam);
   fChain->SetBranchAddress("NClusters", &NClusters, &b_NClusters);
   fChain->SetBranchAddress("NTracks", &NTracks, &b_NTracks);
   fChain->SetBranchAddress("NVetoTracks", &NVetoTracks, &b_NVetoTracks);
   fChain->SetBranchAddress("NSAC", &NSAC, &b_NSAC);
   fChain->SetBranchAddress("NTarget", &NTarget, &b_NTarget);
   fChain->SetBranchAddress("ESAC", ESAC, &b_ESAC);
   fChain->SetBranchAddress("TSAC", TSAC, &b_TSAC);
   fChain->SetBranchAddress("PTypeSAC", PTypeSAC, &b_PTypeSAC);
   fChain->SetBranchAddress("ECluster", ECluster, &b_ECluster);
   fChain->SetBranchAddress("QCluster", QCluster, &b_QCluster);
   fChain->SetBranchAddress("XCluster", XCluster, &b_XCluster);
   fChain->SetBranchAddress("YCluster", YCluster, &b_YCluster);
   fChain->SetBranchAddress("ThCluster", ThCluster, &b_ThCluster);
   fChain->SetBranchAddress("M2Cluster", M2Cluster, &b_M2Cluster);
   fChain->SetBranchAddress("TCluster", TCluster, &b_TCluster);
   fChain->SetBranchAddress("ECell", ECell, &b_ECell);
   fChain->SetBranchAddress("QCell", QCell, &b_QCell);
   fChain->SetBranchAddress("ETracker", ETracker, &b_ETracker);
   fChain->SetBranchAddress("TrackerLay", TrackerLay, &b_TrackerLay);
   fChain->SetBranchAddress("TTracker", TTracker, &b_TTracker);
   fChain->SetBranchAddress("ZTracker", ZTracker, &b_ZTracker);
   fChain->SetBranchAddress("XTracker", XTracker, &b_XTracker);
   fChain->SetBranchAddress("YTracker", YTracker, &b_YTracker);
   fChain->SetBranchAddress("ETarget", &ETarget, &b_ETarget);
   fChain->SetBranchAddress("TTarget", &TTarget, &b_TTarget);
   fChain->SetBranchAddress("XTarget", &XTarget, &b_XTarget);
   fChain->SetBranchAddress("YTarget", &YTarget, &b_YTarget);
   fChain->SetBranchAddress("VetoTrEne", VetoTrEne, &b_NTVetoTrkEne);
   fChain->SetBranchAddress("VetoNFing", VetoNFing, &b_NTVetoTrkFinger);
   fChain->SetBranchAddress("VetoTrTime", VetoTrTime, &b_NTVetoTrkTime);
   fChain->SetBranchAddress("VetoFingE", VetoFingE, &b_NTVetoFingE);
   fChain->SetBranchAddress("VetoX", VetoX, &b_NTVetoX);
   fChain->SetBranchAddress("VetoY", VetoY, &b_NTVetoY);
   Notify();
   return;
}

Bool_t Read101::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   return kTRUE;
}

void Read101::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t Read101::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Read101_cxx

#define Histo_cxx
#include "Histo.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TList.h>
#include <iostream>
#include "cstdlib"
using namespace std;
Histo* Histo::fInstance = 0;
Histo* Histo::GetInstance()
{
  if ( fInstance == 0 ) { fInstance = new Histo(); }
  return fInstance;
}

void Histo::InitHisto()
{
  
  double minMM2 =-200;
  double maxMM2 = 600;
  double NbinsMM2=maxMM2-minMM2;

  //  printf("Initializing  Histograms\n");
  hListGen = new TList();      // list of General histograms to store
  hNTracks = new TH1D("hNTracks", "NTracks", 51, -0.5, 50.5);   
  hETracks = new TH1D("hETracks", "ETracks", 600, 0., 600.);   
  hNTracksRec = new TH1D("hNTracksRec", "NTracksRec", 51, -0.5, 50.5);   
  hETracksRec = new TH1D("hETracksRec", "ETracksRec", 600, 0., 600.);   

  hNCluster= new TH1D("hNCluster","NCluster",11, -0.5, 10.5);   
  hNPosVeto= new TH1D("hNPosVeto","NPosVeto",51, -0.5, 50.5);   
  hNSAC= new TH1D("hNSAC","NSACV",51, -0.5, 50.5);
  hNSACCut= new TH1D("hNSACCut","NSACVCut",51, -0.5, 50.5);
  hEPosVeto= new TH1D("hEPosVeto","EPosVeto",600,0.,600.);   

  hClusterMap  = new TH2D("hClusterMap","ClusterMap",300,-15.,15.,300,-15.,15.); 
  hClusterEvsR = new TH2D("hClusterEvsR","ClusterEvsR",600,0.,600.,80,0.,20.); 
  hClusterE    = new TH1D("hClusterE","ClusterE",600., 0., 600.);   
  hClusterRad  = new TH1D("hClusterRad","ClusterRad",80, 0., 20.);   
  hDtTrkCl     = new TH1D("hDtTrkCl","DtTrkCl",200,-10., 10.);   
  hDtSACCl     = new TH1D("hDtSACCl","DtSACCl",200,-10., 10.);   
  hDtVetoCl    = new TH1D("hDtVetoCl","DtVetoCl",200,-10., 10.);   
  hM2Miss      = new TH1D("hM2Miss","M2Miss",NbinsMM2,minMM2, maxMM2);   
  hM2MissVeto  = new TH1D("hM2MissVeto","M2MissVeto",NbinsMM2,minMM2, maxMM2);   
  hM2Miss3g    = new TH1D("hM2Miss3g","M2Miss3g",NbinsMM2,minMM2, maxMM2);   
  hM2Miss3gSAC = new TH1D("hM2Miss3gSAC","M2Miss3gSAC",NbinsMM2,minMM2, maxMM2);   
  hAccM2Miss   = new TH1D("hAccM2Miss","AccM2Miss",NbinsMM2,minMM2, maxMM2);   
  hClEvsMM2    = new TH2D("hClEvsMM2","ClEvsMM2",600,0.,600.,600,0.,600.);        
  hAccClusterE = new TH1D("hAccClusterE","AccClusterE",600., 0., 600.);   
  hGGMass      = new TH1D("hGGMass","GGMass",300., 0., 30.);   

  hESAC3g  = new TH1D("hESAC3g","hESAC3g",600., 0., 600.); 
  hESAC3gSAC= new TH1D("hESAC3gSAC","hESAC3gSAC",600., 0., 600.); 

  hAccVisEtrk = new TH1D("hAccVisEtrk","AccVisEtrk",600., -600., 600.); 
  hEtotVis    = new TH1D("hEtotVis","EtotVis",600.,0., 600.);   
 
  //Histogram arrays for different mass hypotesis
  hInvThEi     = new TH2D*[20]; 
  hAccThEi     = new TH2D*[20]; 
  hAccClEvsMM2 = new TH2D*[20]; 
  hInvEiTrk    = new TH1D*[20]; 
  hInvMMiss2i  = new TH1D*[20];
  cout<<"Nmasse "<<par->GetNMasses()<<endl;
  //  for(int kk=0;kk<par->GetNMasses();kk++){
  for(int kk=0;kk<11;kk++){
    hInvThEi[kk]    = new TH2D(Form("hInvThEi%d",kk),Form("hInvThEi%d",kk),300,0.,600.,60,0.,12.);
    hInvEiTrk[kk]   = new TH1D(Form("hInvEiTrk%d",kk),Form("hInvEiTrk%d",kk),300,0.,600.);
    hInvMMiss2i[kk] = new TH1D(Form("hInvMMiss%d",kk),Form("hInvMMiss%d",kk),300,0.,900.);
    hAccClEvsMM2[kk]= new TH2D(Form("hAccClEvsMM2%d",kk),Form("hAccClEvsMM2%d",kk),600,0.,600.,600,0.,600.);        
    hAccThEi[kk]    = new TH2D(Form("hAccThEi%d",kk),Form("hAccThEi%d",kk),300,0.,600.,60,0.,12.);

    hListGen->Add(hAccClEvsMM2[kk]);
    hListGen->Add(hInvThEi[kk]);
    hListGen->Add(hAccThEi[kk]);
    hListGen->Add(hInvEiTrk[kk]);
    hListGen->Add(hInvMMiss2i[kk]);
  }
  
  hListGen->Add(hNTracks);
  hListGen->Add(hETracks);

  hListGen->Add(hNTracksRec);
  hListGen->Add(hETracksRec);
  hListGen->Add(hNCluster);
  hListGen->Add(hNPosVeto);
  hListGen->Add(hEPosVeto);
  hListGen->Add(hNSAC);
  hListGen->Add(hNSACCut);
  hListGen->Add(hClusterMap);
  hListGen->Add(hClusterMap);
  hListGen->Add(hClusterEvsR);
  hListGen->Add(hClusterE);
  hListGen->Add(hClEvsMM2);
  hListGen->Add(hClusterRad);

  hListGen->Add(hDtTrkCl); 
  hListGen->Add(hDtSACCl);
  hListGen->Add(hDtVetoCl);
  hListGen->Add(hM2Miss);
  hListGen->Add(hM2MissVeto);

  hListGen->Add(hM2Miss3g);
  hListGen->Add(hM2Miss3gSAC);

  hListGen->Add(hESAC3g);   
  hListGen->Add(hESAC3gSAC);

  hListGen->Add(hAccM2Miss); 
  hListGen->Add(hAccClusterE);

  hListGen->Add(hGGMass);
  hListGen->Add(hAccVisEtrk);
  hListGen->Add(hEtotVis);
}

void Histo::WriteHisto()
{
  printf("Writing  general Histograms\n");
  hListGen->Write();
}

//Costruttore
//#ifdef Histo_cxx
Histo::Histo()
{
  //  printf("Calling Init histograms ");
  par = Param::GetInstance();
  InitHisto();
}
//
Histo::~Histo()
{
//  printf("Closing Init histograms ");
}


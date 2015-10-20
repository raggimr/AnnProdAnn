#define CompAcc_cxx
#include "CompAcc.h"
#include "Read101.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

double CompAcc::CompAccVis(char* ListVis, int nacc)
{

  Double_t NSel=0.;
  Int_t NGood=0;
  Read101 Data;
  printf("Opening file %s\n", ListVis);   
  TFile * fileIn  = TFile::Open(ListVis,"read");   //Open data File!
  TTree * tree  = (TTree*) fileIn->Get("U101");
  fNDPVis=0.;
  TH1D* hist1 = (TH1D*)fileIn->Get("h1");
  fNDPVis=hist1->GetEntries();
  Data.Init(tree);

  Long64_t Nentries=Data.LoopInit();
  if (Nentries<0) return -1;
  while(Data.LoopNext()>=0){
    //cout<<Data.Nevent<<" Clusters "<<Data.NClusters<<" Tracks "<<Data.NTracks<<" "<<Data.NVetoTracks<<endl;
    if(Data.SelectVis(2,nacc)) {
      NGood++;
      //	cout<<kk<<" Event Selected "<<NGood<<endl;
    }
  } //end of loop on events.
  NSel=NGood;
  fAccVis=NSel/fNDPVis;
  fEAccVis=sqrt(fAccVis*(1-fAccVis))/sqrt(fNDPVis);
  cout<<"N DP "<<fNDPVis<<" Event Selected "<<NSel<<" Acc "<<fAccVis<<" +/- "<<fEAccVis<<endl; 
  fileIn->Close();
 //end of loop on files   
}

double CompAcc::CompAccInv(char* ListInv, int nacc)
{
  //  printf("Writing CompAccInv\n");
  Double_t NSel=0.;
  Int_t NGood=0;
  Read101 Data;
  fNDP=0.;  
  //  printf("Opening file %s\n", ListInv);
  TFile * fileIn  = TFile::Open(ListInv,"read");   //Open data File!
  TTree * tree  = (TTree*) fileIn->Get("U101");
  TH1D* hist1 = (TH1D*)fileIn->Get("h1");
  fNDP=hist1->GetEntries();
  //    cout<<"N Dark Photons "<<fNDP[kk]<<endl;
  Data.Init(tree);
  Long64_t Nentries=Data.LoopInit();
  if (Nentries<0) return -1;
  while(Data.LoopNext()>=0){
    //cout<<Data.Nevent<<" Clusters "<<Data.NClusters<<" Tracks "<<Data.NTracks<<" "<<Data.NVetoTracks<<endl;
    if(Data.SelectInv(2,nacc)) {
      NGood++;
      //	cout<<kk<<" Event Selected "<<NGood<<endl;
    }
  } //end of loop on files
  NSel=NGood;
  fAccInv=NSel/fNDP;
  fEAccInv=sqrt(fAccInv*(1-fAccInv))/sqrt(fNDP);
  cout<<"N DP "<<fNDP<<" Event Selected "<<NSel<<" Acc "<<fAccInv<<" +/- "<<fEAccInv<<endl;
  


  fileIn->Close();
  return 1;
}
  
//Costruttore
#ifdef CompAcc_cxx
CompAcc::CompAcc()
{
  his = Histo::GetInstance();
//  printf("Calling Init histograms ");
}
//
CompAcc::~CompAcc()
{
//  printf("Closing Init histograms ");
}
#endif

#define CompBG_cxx
#include "CompBG.h"
#include "Read101.h"
#include "Histo.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

#include "CrystalHandler.h"
#include "Crystal.h"
#include "ClusterFinder.h"
#include "ClusterFinderBox.h"
#include "Cluster.h"

using namespace std;

CompBG::CompBG()
{
  his = Histo::GetInstance();
  printf("Calling Init histograms %d top\n",his);
}
//
CompBG::~CompBG()
{
//  printf("Closing Init histograms ");
}

void CompBG::CompBackG(char* ListBG, int nprim)
{
  FILE* pbg;
  char Line[100];
  Read101 Data;
  Double_t EOT= 1e13;
  Int_t NAnn  = 0;
  printf("Analizing list %s\n",ListBG);
  pbg  = fopen(ListBG,"r");
  if (pbg == NULL){
    printf("Cannot open file %s\n",ListBG);
    exit(-1);
  }
  Data.ZeroNBG();
  Data.ZeroNBGVis();

  //  printf("BG list file succesfully opened: %s\n", ListBG);   
  while( fscanf(pbg, "%s",&Line)!=EOF ){
    printf("Opening file %s\n", Line);   
    TFile * fileIn  = TFile::Open(Line,"read");   //Open data File!
    TTree * tree  = (TTree*) fileIn->Get("U101");
    TH1D* hist1 = (TH1D*)fileIn->Get("h1");
    //    hist1 = (TH1D*)fileIn->Get("h1");
    NtotE = hist1->GetEntries();

    cout<<"Nentries "<<tree->GetEntriesFast()<<" "<<NtotE<<endl;
    cout<<"Total flux analized = "<<NtotE*nprim<<endl;
    cout<<"Fraction of "<<(float)(NtotE*nprim)/EOT<<endl;
    Data.Init(tree);
    Long64_t Nentries=Data.LoopInit();
    if (Nentries<0) return;
    while(Data.LoopNext()>=0){
      //     cout<<Data.Nevent<<" Clusters "<<Data.NClusters<<" Tracks "<<Data.NTracks<<" "<<Data.NVetoTracks<<endl;
      CrystalHandler * CryHand = new CrystalHandler();
      for(int ll=0;ll<900;ll++){
	if(Data.ECell[ll]>0.){
	  int ix=ll%30;
	  int iy=ll/30;
	  //	  cout<<"Filling Crystal "<<ix<<" "<<iy<<endl;
	  Crystal * cry= CryHand->CreateCrystal(ix,iy);
	  cry->SetEnergy(Data.ECell[ll]);
	  //	  cry->SetCharge(Data.QCell[ll]);
	  //	  cry->SetTime(Data.TCell[ll]);
	}
      }
      CryHand->SortEnergy();

      // Find clusters with island algorithm
      ClusterHandler * CluHand = new ClusterHandler();
      ClusterFinder  * CluFind = new ClusterFinder(CryHand,CluHand);
      CluFind->SetEThreshold(0.1);    //min thr in each crystal
      CluFind->SetEThresholdSeed(10.); //min thr for seed crystal
      int newNClu = CluFind->FindClusters();
      his -> Get1DHisto("hNCluDiff")->Fill(newNClu-Data.NClusters);

      // Find clusters with box algorithm
      ClusterHandler* cluHandBox = new ClusterHandler();
      ClusterFinderBox* cluFindBox = new ClusterFinderBox(CryHand,cluHandBox);
      cluFindBox->SetEThreshold(0.1);    //min thr in each crystal
      cluFindBox->SetEThresholdSeed(10.); //min thr for seed crystal
      int newNCluBox = cluFindBox->FindClusters();

      //      cout<<"New "<<newNClu<<" NT "<<Data.NClusters<<endl;
      if(newNClu==Data.NClusters) {
	for(int jj=0;jj<newNClu;jj++){ 
	  //	  cout<<"Enew "<<CluHand->GetCluster(jj)->GetRawEnergy()<<" "<<Data.ECluster[jj]<<endl;
	  his -> Get1DHisto("hECluDiff")->Fill(CluHand->GetCluster(jj)->GetRawEnergy()-Data.ECluster[jj]);
	}
      }
      delete CryHand; //destroy the instance
      delete CluHand; //destroy the instance
      delete CluFind;
      delete cluHandBox; //destroy the instance
      delete cluFindBox;
      if(Data.SelectInv(1,0)==1) { //non ritorna mai perche' hai l'ananlisi in Ei
	his -> Get1DHisto("hNCluster")->Fill(Data.NClusters);
	his -> Get1DHisto("hNSAC")->Fill(Data.NSAC);
	Int_t NcutSAC=0;
	for(int h=0;h<Data.NSAC;h++){
	  if(Data.ESAC[h]>50.) NcutSAC++; 
	}
	his -> Get1DHisto("hNSACCut")->Fill(NcutSAC);
      }
      if(Data.SelectVis(1,0)==1) {
	NBGVis++;
      }
      //      his -> Get1DHisto("hNPosVeto")->Fill(Data.NVetoTracks);
      if(Data.SelectAnn()==1){
	NAnn++;
      }
    }
    NbAnn=NAnn;
    for(int i=0;i<11; i++){ 
      BGMass[i]=Data.GetNBG(i);
      if(BGMass[i]==0) BGMass[i]=1;
      BGMassVis[i]=Data.GetNBGVis(i);
      if(BGMassVis[i]==0) BGMassVis[i]=1;
    }
    fileIn->Close();
  } //end of loop on files   
}

void CompBG::Comp3gBG(char* List3G, int nprim)
{
  FILE* pbg;
  char Line[100];
  Read101 Data;
  Int_t EOT=1E13;
  printf("Analizing list %s\n",List3G);
  pbg  = fopen(List3G,"r");
  if (pbg == NULL){
    printf("Cannot open file %s\n",List3G);
    exit(-1);
  }
  Data.ZeroNBG3g();
  Data.ZeroNBG3gVis();
  //  printf("BG list file succesfully opened: %s\n", ListBG);   
  while( fscanf(pbg, "%s",&Line)!=EOF ){
    printf("Opening file %s\n", Line);   
    TFile * fileIn  = TFile::Open(Line,"read");   //Open data File!
    TTree * tree  = (TTree*) fileIn->Get("U101");
    TH1D* hist1 = (TH1D*)fileIn->Get("h1");
    NtotE = hist1->GetEntries();

    Param* par = Param::GetInstance();
    double ThreeGp = par->Get3gProb();
    Int_t NMaxEvents=NtotE*ThreeGp;
    cout<<"Nmax 3g events "<<NMaxEvents<<endl;
    cout<<"Nentries "<<tree->GetEntriesFast()<<" "<<NtotE<<endl;
    cout<<"Total flux analized = "<<NtotE*nprim<<endl;
    cout<<"Fraction of "<<(float)(NtotE*nprim)/EOT<<endl;
    Data.Init(tree);
    Long64_t Nentries=Data.LoopInit();
    if (Nentries<0) return;
    while(Data.LoopNext()>=0 && Data.Nevent<NMaxEvents){
      //cout<<Data.Nevent<<" Clusters "<<Data.NClusters<<" Tracks "<<Data.NTracks<<" "<<Data.NVetoTracks<<endl;
      if(Data.SelectInv(3,0)==1) { //flag 3 for 3g analysis
	his -> Get1DHisto("hNCluster")->Fill(Data.NClusters);
	his -> Get1DHisto("hNSAC")->Fill(Data.NSAC);
	Int_t NcutSAC=0;
	for(int h=0;h<Data.NSAC;h++){
	  if(Data.ESAC[h]>20) NcutSAC++; 
	}
	his -> Get1DHisto("hNSACCut")->Fill(NcutSAC);
      }
      if(Data.SelectVis(1,0)==1) {
	NBG3gVis++;
      }
      //      his -> Get1DHisto("hNPosVeto")->Fill(Data.NVetoTracks);
      //      if(Data.SelectAnn()==1){
      //	NAnn++;
    }
    for(int i=0;i<11; i++){ 
      BG3gMass[i]=Data.GetNBG3g(i);
      if(BG3gMass[i]==0) BG3gMass[i]=1;
      BG3gMassVis[i]=Data.GetNBG3gVis(i);
      if(BG3gMassVis[i]==0) BG3gMassVis[i]=1;
      cout<<"N3g INV "<<BG3gMass[i] <<" "<<endl;
    }  
    fileIn->Close();
  }
}


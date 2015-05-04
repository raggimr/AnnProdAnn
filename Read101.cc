#define Read101_cxx
#include "Read101.h"
#include <TH1D.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

Read101::Read101(TTree *tree)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  his = Histo::GetInstance();
  par = Param::GetInstance();
  // par->InitCut();
  T0 = new CompT0;
  if (tree == 0) {
    //      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("UBTF.root");
    //      if (!f) {
    //         f = new TFile("UBTF.root");
    //      }
    tree = (TTree*)gDirectory->Get("U101");
  }
  Init(tree);
}

Long64_t Read101::LoopInit(){
   if (fChain == 0) return -1;
   fNentries = fChain->GetEntriesFast();
   fJentry=0;
   fNbytes=0;
   //   for(int ll=0;ll<11;ll++) NBGMass[ll]=0.;
   return fNentries;
}

Long64_t Read101::LoopNext(){
  if(fJentry>=fNentries) return -1;
  Long64_t ientry = LoadTree(fJentry);
  if (ientry < 0) return -2;
  Long64_t nb = fChain->GetEntry(fJentry);   fNbytes += nb;
  fJentry++;
  return nb;
}

void Read101::Loop()
{

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
//      cout<<""<<NClusters<<" "<<NTracks<<" "<<NVetoTracks<<endl;
//      hNTracks ->Fill(NTracks);
//      hNCluster->Fill(NClusters);
//      hNPosVeto->Fill(NVetoTracks);
//      hNSACVeto->Fill(NNGVeto);
   }
}

Int_t Read101::SelectVis(Int_t Doplot,Int_t nacc)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns  0 otherwise.
  int NInTimeTrk=0;
  int Nep=0,Nem=0;
  int iele=0,ipos=0;
  Double_t TWind=par->GetTWindVis();
  Double_t DtTrkCl;

  if(NClusters!=1)   return 0; // add timing cuts on the clusters
  double ClRad = sqrt(XCluster[0]*XCluster[0]+YCluster[0]*YCluster[0]);
  if(ClRad<5.|| ClRad>13.)                return 0;  // Geometrical Cuts
  for(int ll=0; ll<NTracks; ll++){ 
   
    DtTrkCl=(TCluster[0]-T0->CorrectCellT(XCluster[0],YCluster[0]))-(TTracker[ll]-T0->CorrectTrackT(ETracker[ll]));
    
    if(ETracker[ll]<0. && fabs(DtTrkCl)<TWind) {
      Nem++;
      iele=ll;
      if(Doplot==2) his -> Get1DHisto("hAccVisEtrk")->Fill(ETracker[ll]);
    }
    if(ETracker[ll]>0 && fabs(DtTrkCl)<TWind){
      Nep++;
      ipos=ll;
      if(Doplot==2) his -> Get1DHisto("hAccVisEtrk")->Fill(ETracker[ll]);
    }
  }
 
  //  cout<<"NBGvis Ee "<<ETracker[iele]<<" Ep "<<ETracker[ipos]<<" "<<ECluster[0]<<endl;
  if(Nep!=1 || Nem!=1) return 0;  //ask for one e+ e- pair in time with the gamma

  double Tele = TTracker[iele]-T0->CorrectTrackT(ETracker[iele]); 
  double Tpos = TTracker[ipos]-T0->CorrectTrackT(ETracker[ipos]);
  double DtTrkTrk= Tele-Tpos;

  if(fabs(DtTrkTrk)>TWind) return 0;
  Double_t ETOT=abs(ETracker[iele])+ETracker[ipos]+ECluster[0];
  if(Doplot==1) his -> Get1DHisto("hEtotVis")->Fill(ETOT);
  //  cout<<"ETOT "<<ETOT<<" "<<ETracker[iele]<<" "<<ETracker[ipos]<<" "<<ECluster[0]<<endl;
  if(ETOT>570 || ETOT<530) return 0;
  if(Doplot==1){ //means BG analysis with mass intervals
    for(int kk=0;kk<11;kk++){
      if(ECluster[0]<par->GetMinECl(kk) || ECluster[0]>par->GetMaxECl(kk)) continue;
      if(M2Cluster[0]< (par->GetMeanMM2(kk)-par->GetRMSMM2(kk)) || M2Cluster[0]>(par->GetMeanMM2(kk)+par->GetRMSMM2(kk)) ) continue;
      NBGMassVis[kk]++;
    }
  }else{ //Acceptance analysis
    if(ECluster[0]<par->GetMinECl(nacc) || ECluster[0]>par->GetMaxECl(nacc)) return 0;
    if(M2Cluster[0]< (par->GetMeanMM2(nacc)-par->GetRMSMM2(nacc)) || M2Cluster[0]>(par->GetMeanMM2(nacc)+par->GetRMSMM2(nacc)) ) return 0;
  }
  return 1;
}

Int_t Read101::SelectAnn()
{
  Double_t ClRad[2];
  Int_t ii;
  Double_t MinClRad=par->GetMinClRad();
  Double_t MaxClRad=par->GetMaxClRad();

  if(NClusters!=2)   return -1; // add timing cuts on the clusters
  for(ii=0;ii<2;ii++){          // clusters acceptance
    ClRad[ii]= sqrt(XCluster[ii]*XCluster[ii]+YCluster[ii]*YCluster[ii]);
    if(ClRad[ii]<MinClRad|| ClRad[ii]>MaxClRad)               return 0;  // Geometrical Cuts
    if(ECluster[ii]<50.|| ECluster[ii]>400.)                  return 0;
  }
  Double_t MassGG=GGMass();
  //  cout <<"GGMASS "<< MassGG <<endl;
  his -> Get1DHisto("hGGMass")->Fill(MassGG);
  if(MassGG<18.)                   return 0;
  return 1;
}


Double_t Read101::GGMass()
{
  double ECalPosiZ=180; //
  if(NClusters!=2)                        return -1;  // Need 2 clusters
  double XDiff2 = (XCluster[0]-XCluster[1])*(XCluster[0]-XCluster[1]);
  double YDiff2 = (YCluster[0]-YCluster[1])*(YCluster[0]-YCluster[1]);
  //  double Massa  = sqrt(ECluster[0]*ECluster[1]*(XDiff2+YDiff2))/(ECalPosiZ-ECalSizeZ*0.5);
  double Massa  = sqrt(ECluster[0]*ECluster[1]*(XDiff2+YDiff2))/(ECalPosiZ);
  //  cout<<"Massa "<<Massa<<endl;
  return Massa;
}

Int_t Read101::SelectInv(Int_t Doplot,Int_t nacc)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns  0 otherwise.
//  Param par;
//  par->WriteParam();
  int NInTimeTrk=0;
  int NInTimeVeto=0;
  int NInTimeSAC=0;
  int NGoodTrk=0;
  Double_t TWind   = par->GetTWindInv();
  Double_t MinClRad= par->GetMinClRad();
  Double_t MaxClRad= par->GetMaxClRad();

  if(NClusters!=1.) return 0;
  double ClRad = sqrt(XCluster[0]*XCluster[0]+YCluster[0]*YCluster[0]);
  if(Doplot==1) his -> Get1DHisto("hClusterEvsR")->Fill(ECluster[0],ClRad);
  if(ClRad<MinClRad || ClRad>MaxClRad)                return 0;  // Geometrical Cuts
  if(ECluster[0]>400. || ECluster[0]<20.) return 0;  // Cluster Energy Cuts

  if(Doplot==1){
    his -> Get2DHisto("hClusterMap")->Fill(XCluster[0],YCluster[0]);
    his -> Get1DHisto("hClusterE")  ->Fill(ECluster[0]);
    his -> Get1DHisto("hClusterRad")->Fill(ClRad);
    his -> Get1DHisto("hNTracks")   ->Fill(NTracks);
    for(int ll=0; ll<NTracks; ll++){ 
      his -> Get1DHisto("hETracks")->Fill(ETracker[ll]);
      if(TrackerLay[ll]<=8 || TrackerLay[ll]==17){
	his -> Get1DHisto("hETracksRec")->Fill(ETracker[ll]);
	NGoodTrk++;
      }
    }
    his -> Get1DHisto("hNTracksRec")->Fill(NGoodTrk);
    his -> Get1DHisto("hNPosVeto")  ->Fill(NVetoTracks);
    for(int ll=0; ll<NVetoTracks; ll++) his -> Get1DHisto("hEPosVeto")->Fill(VetoTrEne[ll]);
  }
  NInTimeTrk  = IsTrkInTime(0,TWind);
  NInTimeVeto = IsVetoInTime(0,TWind);
  NInTimeSAC  = IsSACInTime(0,TWind);
  for(int i=0;i<NTracks;i++)     his -> Get1DHisto("hDtTrkCl")->Fill(DtTrkCl[i]);
  for(int i=0;i<NVetoTracks;i++) his -> Get1DHisto("hDtVetoCl")->Fill(DtVetoCl[i]);
  for(int i=0;i<NSAC;i++)        his -> Get1DHisto("hDtSACCl")->Fill(DtSACCl[i]);
    
  //  cout<<"Nintime "<<NInTimeTrk<<" Veto "<<NInTimeVeto<<" "<<NInTimeSAC<<" "<<ECluster[0]<<endl;
  if(Doplot==1) his -> Get1DHisto("hM2Miss")->Fill(M2Cluster[0]);
  if(NInTimeTrk>0) return 0;
  if(Doplot==3) his -> Get1DHisto("hM2Miss3g")->Fill(M2Cluster[0]);
  //  if(Doplot==3) his -> Get1DHisto("hESAC3g")->Fill(ESAC);
  //  if(NInTimeTrk>0 || NInTimeVeto>0) return 0; 
  if(NInTimeSAC>0) return 0; 
  if(Doplot==3) his -> Get1DHisto("hM2Miss3gSAC")->Fill(M2Cluster[0]);

  if(Doplot==1 || Doplot==3){ //1 means BG analysis or 3 means 3G analysis
    if(Doplot==1) his -> Get1DHisto("hM2MissVeto")->Fill(M2Cluster[0]);
    his -> Get2DHisto("hClEvsMM2")->Fill(ECluster[0],M2Cluster[0]);
    for(int kk=0;kk<11;kk++){
      if(ECluster[0]<par->GetMinECl(kk) || ECluster[0]>par->GetMaxECl(kk)) continue;
      if(M2Cluster[0]< (par->GetMeanMM2(kk)-par->GetRMSMM2(kk)) || M2Cluster[0]>(par->GetMeanMM2(kk)+par->GetRMSMM2(kk)) ) continue;
      //cout<<"limits "<<par->GetMinECl(kk)<<" Max "<<par->GetMaxECl(kk)<<"ECluster "<<ECluster[0]<<endl;
      his -> Get1DHisto(Form("hInvMMiss%d",kk))->Fill(M2Cluster[0]);
      his -> Get1DHisto(Form("hInvEiTrk%d",kk))->Fill(ETracker[0]);
      his -> Get2DHisto(Form("hInvThEi%d",kk)) ->Fill(ECluster[0],ThCluster[0]);
      if (Doplot==1) NBGMass[kk]++;
      if (Doplot==3) NBG3gMass[kk]++;
      //      cout<<"Pbeam "<<NBG3gMass[kk]<<endl;
    }
  }else if(Doplot==2){ //Acceptance analysis
    his -> Get1DHisto("hAccM2Miss")  ->Fill(M2Cluster[0]);
    his -> Get1DHisto("hAccClusterE")->Fill(ECluster[0]);
    if(ECluster[0]<par->GetMinECl(nacc) || ECluster[0]>par->GetMaxECl(nacc)) return 0;
    if(M2Cluster[0]< (par->GetMeanMM2(nacc)-par->GetRMSMM2(nacc)) || M2Cluster[0]>(par->GetMeanMM2(nacc)+par->GetRMSMM2(nacc)) ) return 0;
    his -> Get2DHisto(Form("hAccClEvsMM2%d",nacc))->Fill(ECluster[0],M2Cluster[0]); 
    his -> Get2DHisto(Form("hAccThEi%d",nacc)) ->Fill(ECluster[0],ThCluster[0]);
  }
  return 1;
}

//Track to Cluster timing
Int_t Read101::IsTrkInTime(int nclu, double wind)
{
  int InTime=0;
  for(int i=0;i<NTracks;i++) InTimeTrkInd[i]=0;
  
  for(int i=0;i<NTracks;i++){
    if(ETracker[i]>2.){
      DtTrkCl[i]=(TCluster[nclu]-T0->CorrectCellT(XCluster[nclu],YCluster[nclu]))-(TTracker[i]-T0->CorrectTrackT(ETracker[i]));
      if(fabs(DtTrkCl[i])<wind){
	InTimeTrkInd[InTime]=i;
	InTime++;
      }
    }
  }
  return InTime;
}

Int_t Read101::IsVetoInTime(int nclu, double wind) //Sbagliato!!!!!! Devi usare la Z
{
  int InTime=0;
  for(int i=0;i<NVetoTracks;i++){
    //    cout<<"Veto Y"<<VetoY[i] <<endl;
    if(VetoTrEne[i]>2. && VetoY[i]<-760.){
      DtVetoCl[i]=(TCluster[nclu]-T0->CorrectCellT(XCluster[nclu],YCluster[nclu]))-(VetoTrTime[i]-T0->CorrectTrackEVeto(VetoTrEne[i])); 
      if(fabs(DtVetoCl[i])<wind) InTime++;
    }
  }
  return InTime;
}
Int_t Read101::IsSACInTime(int nclu, double wind){
  int InTime=0;
  for(int i=0;i<NSAC;i++){
    if(ESAC[i]>50.){
      DtSACCl[i]=(TCluster[nclu]-T0->CorrectCellT(XCluster[nclu],YCluster[nclu]))-(TSAC[i]-T0->CorrectSACT(0.,0.));
      if(fabs(DtSACCl[i])<wind/2) InTime++;
    }
  }
  return InTime;
}

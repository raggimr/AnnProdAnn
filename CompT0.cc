#define CompT0_cxx
#include "CompT0.h"
#include "Read101.h"
#include "Histo.h"

#include <iostream>
#include "cstdlib"
#include "math.h"
using namespace std;

double CompT0::DoT0(char* ListT0)
{
  FILE* pbg;
  char Line[100];
  Read101 Data;
  printf("Analizing list %s\n",ListT0);
  pbg  = fopen(ListT0,"r");
  if (pbg == NULL){
    printf("Cannot open file %s\n",ListT0);
    exit(-1);
  }
  printf("Visible list file succesfully opened: %s\n", ListT0);   
  while( fscanf(pbg, "%s",&Line)!=EOF ){
    printf("Opening file %s\n", Line);   
     TFile * fileIn  = TFile::Open(Line,"read");   //Open data File!
     TTree * tree  = (TTree*) fileIn->Get("U101");
     //     cout<<"Nentries "<<tree->GetEntriesFast()<<endl;
     Data.Init(tree);
     Data.Loop();
     fileIn->Close();
  } //end of loop on files   
}

//Costruttore
#ifdef CompT0_cxx
CompT0::CompT0()
{
//  printf("Calling Init histograms ");
}
//
CompT0::~CompT0()
{
//  printf("Closing Init histograms ");
}

double CompT0::CorrectCellT(Double_t XCell, Double_t YCell)
{
  double TCorr;
  const double ZTarg = -20.; //cm
  const double XTarg = 0;
  const double YTarg = 0;
  const double ZCal  = 160.; // cm
  const double C     = 3E10; // cm/s
  //  TCorr=sqrt((XCell-XTarg)*(XCell-XTarg)+(YCell-YTarg)*(YCell-YTarg)+(ZCal-ZTarg)*(ZCal-ZTarg))/C;
  //  return TCorr*1e9; //Return time in ns
  TCorr=6.3;
  return TCorr;
}

double CompT0::CorrectTrackT(Double_t TrackP){
  double TCorr;
  //  TCorr=1.27183+TrackP*0.0115232-TrackP*TrackP*2.03813e-05+1.7811e-08*TrackP*TrackP*TrackP;
  TCorr=1.5+TrackP*0.00742-TrackP*TrackP*-1.086e-06-8.6311e-09*TrackP*TrackP*TrackP;
  return TCorr; //Return time in ns
}

double CompT0::CorrectTrackEVeto(Double_t TrackP){
  double TCorr;
  //  TCorr=8.10461-0.0040822*TrackP+TrackP*TrackP*2.62277e-05-3.01633e-08*TrackP*TrackP*TrackP;
  TCorr=9.7;
  return TCorr; //Return time in ns
}

double CompT0::CorrectSACT(Double_t XSAC, Double_t YSAC)
{
  double TCorr;
  const double ZTarg = -20.; //cm
  const double XTarg = 0;
  const double YTarg = 0;
  const double ZSAC  = 224.; // cm
  const double C     = 3e10; // cm/s
  TCorr=sqrt((XSAC-XTarg)*(XSAC-XTarg)+(YSAC-YTarg)*(YSAC-YTarg)+(ZSAC-ZTarg)*(ZSAC-ZTarg))/C;
  return TCorr*1e9; //Return time in ns
}
#endif

#define Param_cxx
#include "Param.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TList.h>
#include <iostream>
#include "cstdlib"
using namespace std;
Param* Param::fInstance = 0;
Param* Param::GetInstance()
{
  if ( fInstance == 0 ) { fInstance = new Param(); }
  return fInstance;
}

void Param::InitParam()
{
  FILE *parfile;
  char line[200];
  int offset;
  float valo;

  //  printf("Calling parameter init\n");
  //  line    = (char *) malloc(100*sizeof(char));
  parfile  = fopen("param.txt","r");
  if (parfile == NULL){
    printf("Cannot open param file\n");
    exit(-1);
  }
  printf("Parameter file succesfully opened\n");
  fgets(line,160,parfile);
  if(line[0]=='#') fgets(line,160,parfile);
  sscanf(line,"%f %f %f %f %d",&IsInvAnOn,&IsVisAnOn,&IsDoAcc,&Is3gOn,&NMasses);
  fgets(line,160,parfile);
  if(line[0]=='#') fgets(line,160,parfile);
  sscanf(line,"%f %f %f",&AnnCross,&tregCross,&Dtarg);
  //Compute annihilation probability on carbon 
  Double_t ZN = 6.;
  Double_t NA = 6.022e23 ; //Avogadro number
  Double_t MC = 12.;
  Double_t RC = 2.62;
  Double_t sigmaAnni=AnnCross*1e-36;
  Double_t VT = Dtarg;     //in cm3
  AnnProb = sigmaAnni*ZN*NA*RC*VT/MC;
  tregProb= tregCross*1e-36*ZN*NA*RC*VT/MC;;
  cout<<"Targ th "<<Dtarg<<" AnnProb "<<AnnProb<<" 3gProb "<<tregProb<<endl;
  // Get the ee->Ug cross at 550MeV
  fgets(line,100,parfile);
  if(line[0]=='#') fgets(line,160,parfile);
  char *data = line;
  int i=0;
  while (sscanf(data, " %f%n", &valo, &offset) == 1)
    {
      sigmaUg[i] = valo;
      data += offset;
      Delta[i]=sigmaUg[i]*1E6/AnnCross; //go to eps=1
      //      cout<<sigmaUg[i]<<" "<<AnnCross<<" Delta "<<Delta[i]<<" i "<<i<<endl;
      i++;
    }
  
  // Get the ee->Ug cross at 750MeV
  fgets(line,160,parfile);
  if(line[0]=='#') fgets(line,160,parfile);
  char *data1 = line;
  int j=0;			
  while (sscanf(data1, " %f%n", &valo, &offset) == 1)
    {
      sigmaUg750[j] = valo;
      data1 += offset;
      Delta750[j]=sigmaUg750[j]*1E6/AnnCross; //go to eps=1
      //      cout<<"750 "<<sigmaUg750[j]<<" "<<AnnCross<<" Delta "<<Delta750[j]<< " j " <<j<<endl;
      j++;
    }
  fclose(parfile);
}

void Param::InitCut()
{
  FILE *cutfile;
  char line[200];// "";
  int offset;
  float valo;
  int i=0;

  cutfile  = fopen("cut.txt","r");
  if (cutfile == NULL){
    printf("Cannot open param file\n");
    exit(-1);
  }
  //  printf("NMasses %d\n",NMasses);
  printf("Cut file succesfully opened\n");

  fgets(line,160,cutfile);
  cout<<line<<endl;
  while(line[0]=='#') fgets(line,160,cutfile);
  sscanf(line,"%f %f",&MinClRad,&MaxClRad);

  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  sscanf(line,"%f %f",&TWindInv,&TWindVis);

  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  char *data = line;			
  //  printf("%s",line);
  while (sscanf(data, " %f%n", &valo, &offset) == 1)
    {
      MinClEne[i] = valo; //MinClEne->PushBack(valo)
      data += offset;
      //      printf("read: %f", MinClEne[i]);
      i++;
    }
  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  i=0;
  char *data1 = line;			
  while (sscanf(data1, " %f%n", &valo, &offset) == 1)
    {
  
      MaxClEne[i] = valo;
      data1 += offset;
      //      printf("read: %f", MaxClEne[i]);
      i++;
    }

  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  i=0;
  char *data2 = line;			
  while (sscanf(data2, " %f%n", &valo, &offset) == 1)
    {
      MeanMM2[i] = valo;
      data2 += offset;
      i++;
      //      printf("read: %f", MeanMM2[i]);
    }

  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  i=0;
  char *data3 = line;			
  while (sscanf(data3, " %f%n", &valo, &offset) == 1)
    {
      RMSMM2[i] = valo;
      data3 += offset;
      i++;
      //     printf("read: %f", MinClEne[i]);
    }

  fgets(line,160,cutfile);
  while(line[0]=='#') fgets(line,160,cutfile);
  i=0;
  char *data4 = line;			
  while (sscanf(data4, " %f%n", &valo, &offset) == 1)
    {
      UMass[i] = valo;
      data4 += offset;
      //      printf("read: %f\n", UMass[i]);
      i++;
    }
}

void Param::WriteParam()
{
  printf("NMasses %d\n",NMasses);
  printf("Ann Cross %f\n",AnnCross);
  for (int i=0; i<11; i++) printf("%f %f %f %f %f\n",MinClEne[i],MaxClEne[i],MeanMM2[i],RMSMM2[i],UMass[i]);
}

Param::Param()
{
//  printf("Calling Init histograms ");
}
//
Param::~Param()
{
//  printf("Closing Init histograms ");
}



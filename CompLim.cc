#define CompLim_cxx
#include "CompLim.h"
#include "Read101.h"

#include <iostream>
#include "cstdlib"
#include "math.h"
using namespace std;

double CompLim::CompLimVis(double NBG, double Ngg,double Accgg,double AccUg,double Delta)
{
  Double_t   NLimit=0;
  if(NBG==0) NBG=1.29;  //68% CL
  cout<< "Limite "<<NBG<<" "<<Ngg<<" "<<Accgg<<" "<<AccUg<<" "<<Delta<<endl;
  NLimit=(sqrt(NBG)/Ngg)*(Accgg/AccUg)/Delta;
  return NLimit;
  printf("Computing visible limit using %f %f %f\n",NBG,Ngg, Ngg/(Accgg*1.2e-5));
}

double CompLim::CompLimInv(double NBG, double Ngg, double Accgg,double AccUg,double Delta)
{
  Double_t   NLimit=0;
  if(NBG==0) NBG=1.29;  //68% CL
  cout<< "Limite "<<NBG<<" "<<Ngg<<" "<<Accgg<<" "<<AccUg<<" "<<Delta<<endl;
  NLimit=(sqrt(NBG)/Ngg)*(Accgg/AccUg)/Delta;
  return NLimit;
  // printf("Computing Invisible limit using %f %f\n",NBG,Ngg);
}

//Costruttore
#ifdef CompLim_cxx
CompLim::CompLim()
{
//  printf("Calling Init histograms ");
}
//
CompLim::~CompLim()
{
//  printf("Closing Init histograms ");
}
#endif

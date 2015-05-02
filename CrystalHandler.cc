#define CrystalHandler_cxx
#include <algorithm>
#include "CrystalHandler.h"
#include "Read101.h"
#include "Histo.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//Costruttore
#ifdef CrystalHandler_cxx
CrystalHandler::CrystalHandler()
{
  fNCrystals=0;
  //Clean Crystal map
  for(int i=0;i<30;i++){
    for(int j=0;j<30;j++){
      fCrystalMap[i][j]=0;
    }
  }
}

CrystalHandler::~CrystalHandler()
{
  //  cout <<"ti distruggo"<<endl; 
  // Kill all pointers to the crystals of the event
  for(int kk; kk<fNCrystals;kk++){
    delete fCrystalList[kk];
  }
}

Crystal* CrystalHandler::CreateCrystal(int ix,int iy)
{
  if(fCrystalMap[ix][iy]!=0){
    cout<<"Already existing Crystal "<<endl;
    return fCrystalMap[ix][iy];
  }
  Crystal * cry = new Crystal(ix,iy);
  fCrystalList[fNCrystals++]=cry;
  fCrystalMap[ix][iy]=cry;
  return cry;
}

bool SortByEnergy(Crystal*a ,Crystal*b)
{
  return (a->GetEnergy() > b->GetEnergy());
}

void CrystalHandler::SortEnergy()
{
  std::sort(fCrystalList,fCrystalList+fNCrystals,SortByEnergy);
}

int CrystalHandler::FindSeeds(double thr)
{
  int nseed=0;
  for(int kk=0;kk<fNCrystals;kk++){
    if( fCrystalList[kk]->GetEnergy()>= thr) {
      fCrystalList[kk]->SetSeed();
      nseed++;
    }
  }
  return nseed;
}

void CrystalHandler::Print()
{
  cout<<"I know "<<fNCrystals<<" Crystals "<<endl;
  for(int kk=0;kk<fNCrystals;kk++){
    fCrystalList[kk]->Print();
  }
}




#endif

#include "CrystalHandler.h"

#include "GeomParam.h"

#include <algorithm>
#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//Costruttore
CrystalHandler::CrystalHandler()
{

  fNCrystals=0;

  // Get current number of crystals being used
  GeomParam* geo = GeomParam::GetInstance();
  fNCryX = geo->GetNCryX();
  if (fNCryX>CRYSTALHANDLER_N_MAX_CRYSTALS_X) {
    cout<<"ERROR - CrystalHandler::CrystalHandler - Too many crystals along X: redefine CRYSTALHANDLER_N_MAX_CRYSTALS_X"<<endl;
    exit(1);
  }
  fNCryY = geo->GetNCryY();
  if (fNCryY>CRYSTALHANDLER_N_MAX_CRYSTALS_Y) {
    cout<<"ERROR - CrystalHandler::CrystalHandler - Too many crystals along Y: redefine CRYSTALHANDLER_N_MAX_CRYSTALS_Y"<<endl;
    exit(1);
  }

  //Clean Crystal map
  for(int i=0;i<fNCryX;i++){
    for(int j=0;j<fNCryY;j++){
      fCrystalMap[i][j]=0;
    }
  }
}

CrystalHandler::~CrystalHandler()
{
  // Kill all pointers to the crystals of the event
  for(int kk; kk<fNCrystals;kk++){
    delete fCrystalList[kk];
  }
}

Crystal* CrystalHandler::GetSeed(double Ethr)
{
  for(int kk; kk<fNCrystals;kk++){
    if ( !(fCrystalList[kk]->IsUsed()) && (fCrystalList[kk]->GetEnergy() > Ethr) ) { 
      return fCrystalList[kk];
    }
  }
  return 0;
}

Crystal* CrystalHandler::CreateCrystal(int ix,int iy)
{
  if (ix<0 || ix>=fNCryX || iy<0 || iy>=fNCryY) {
    cout<<"WARNING - CrystalHandler::CreateCrystal - Attept to create crystal outside map: "<<ix<<" "<<iy<<endl;
    return 0;
  }
  if(fCrystalMap[ix][iy]!=0){
    cout<<"WARNING - CrystalHandler::CreateCrystal - Attept to create already existing crystal: "<<ix<<" "<<iy<<endl;
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
  if (fNCrystals) {
    std::sort(fCrystalList,fCrystalList+fNCrystals,SortByEnergy);
  }
}

void CrystalHandler::Print()
{
  cout<<"I know "<<fNCrystals<<" Crystals "<<endl;
  for(int kk=0;kk<fNCrystals;kk++){
    fCrystalList[kk]->Print();
  }
}

Crystal* CrystalHandler::GetCrystal(int ix,int iy)
{
  if (ix<0 || ix>=fNCryX || iy<0 || iy>=fNCryY) {
    //cout<<"WARNING - CrystalHandler::GetCrystal(map) - Attept to access crystal outside map: "<<ix<<" "<<iy<<endl;
    return 0;
  }
  return fCrystalMap[ix][iy];
}

Crystal* CrystalHandler::GetCrystal(int i)
{
  if (i<0 || i>=fNCrystals) {
    cout<<"WARNING - CrystalHandler::GetCrystal(list) - Attept to access crystal outside list: "<<i<<endl;
    return 0;
  }
  return fCrystalList[i];
}

Crystal* CrystalHandler::GetCrystal(double x, double y)
{
  // Will be implemented when GeometryParameters is available
  return 0;
}

void CrystalHandler::ResetCrystals()
{
  for(int i=0; i<fNCrystals; i++){
    fCrystalList[i]->ResetUsed();
    fCrystalList[i]->ResetSeed();
  }
}

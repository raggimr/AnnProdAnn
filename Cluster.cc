#include "Cluster.h"

#include "Crystal.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//Costruttore
Cluster::Cluster()
{
  fRawEnergy=0;
  fEnergy=-1;
  fTime=-1;
  fXCenter  =-99.;	 
  fYCenter  =-99.;	
  fNCrystals=  0;
}

Cluster::~Cluster()
{;}

int Cluster::AddCrystal(Crystal* crystal)
{
  if (crystal->IsUsed()) {
    cout<<"ERROR - Cluster::AddCrystal - Try to add already USED crystal"<<endl;
    return -1;
  }
  if(fNCrystals<CLUSTER_N_MAX_CRYSTALS_IN_CLUSTER){
    fCrystalList[fNCrystals]=crystal;
    fNCrystals++;
    crystal->SetUsed();
    fRawEnergy += crystal->GetEnergy();
    return fNCrystals;
  } else {
    cout<<"WARNING - Cluster::AddCrystal - Too many crystals in cluster: "<<fNCrystals<<endl;
    return fNCrystals;
  }
}

void Cluster::Print()
{
  cout<<"X "<<fXCenter<<" Y "<<fYCenter<<" Energy "<<fEnergy<<" Raw Energy "<<fRawEnergy<<" Time "<<fTime<<" NCry "<<fNCrystals<<endl;
}

double Cluster::ComputeTime()
{
  cout<<"WARNING - Cluster::ComputeTime - Not implemented"<<endl;
  return 0.;
}

double Cluster::ComputeEnergy()
{
  cout<<"WARNING - Cluster::ComputeEnergy - Not implemented"<<endl;
  return 0.;
}

double Cluster::ComputeCenter()
{
  cout<<"WARNING - Cluster::ComputeCenter - Not implemented"<<endl;
  return 0.;
}

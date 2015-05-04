#include "Cluster.h"
#include "Crystal.h"
#include "Histo.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//  ECAL Dimension
const double CalSizeX =30.;   //in cm
const double CalSizeY =30.;   //in cm
const double CalSizeZ =22.;   //in cm full scale length

const int CalNRow       = 30;
const int CalNCol       = 30;

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
{

}

int Cluster::AddCrystal(Crystal* crystal)
{
  if(fNCrystals<NMAXCRYSTALSINCLUSTER){
    fCrystalList[fNCrystals]=crystal;
    fNCrystals++;
    crystal->SetUsed();
    return fNCrystals;
  }
}

void Cluster::Print()
{
  cout<<fXCenter<<" "<<fYCenter<<" Energy "<<fEnergy<<" Raw Energy "<<fRawEnergy<<" Time "<<fTime<<endl;
}

#define Crystal_cxx
#include "Crystal.h"
#include "Read101.h"
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
#ifdef Crystal_cxx
Crystal::Crystal(int ix ,int iy)
{
  fEnergy=-1;
  fTime=-1;
  fCharge=-1;
  fXi=ix;
  fYi=iy;
  fUsed=0;
  fSeed=0;

}

Crystal::~Crystal()
{

}




double Crystal::GetXCenter(){
  double CryX  = CalSizeX/CalNRow;
  double Xcoord=-CalSizeX*0.5+0.5*CryX+fXi*CryX;

}

double Crystal::GetYCenter(){
  double CryY  = CalSizeY/CalNCol;
  double Ycoord=-CalSizeY*0.5+0.5*CryY+fYi*CryY;
}



void Crystal::Print()
{
  cout<<fXi<<" "<<fYi<<" "<<fUsed<<" "<<fSeed<<" Energy "<<fEnergy<<" Charge "<<fCharge<<" Time "<<fTime<<endl;
}


#endif

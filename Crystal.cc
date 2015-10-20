#include "Crystal.h"

#include "GeomParam.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//Costruttore
Crystal::Crystal(int ix ,int iy)
{

  GeomParam* geo = GeomParam::GetInstance();

  double calFrontFaceCenterX = 0.;
  double calFrontFaceCenterY = 0.;
  double calFrontFaceCenterZ = geo->GetECalToTarg();

  int calNCryX = geo->GetNCryX();
  int calNCryY = geo->GetNCryY();

  double cryXSize = geo->GetCryXSize();
  double cryYSize = geo->GetCryYSize();
  double cryZSize = geo->GetCryZSize();

  // Verify if crystal to be created is inside the map
  if ( ix<0 || ix>=calNCryX || iy<0 || iy>=calNCryY ){
    cout<<"ERROR - Crystal::Crystal - Crystal outside map: "<<ix<<" "<<iy<<endl;
    exit(1);
  }

  fXi=ix;
  fYi=iy;

  fStatus=0;

  fEnergy=-1;
  fTime=-1;
  fCharge=-1;

  fXCenter = calFrontFaceCenterX+cryXSize*(-0.5*calNCryX+0.5+ix);
  fYCenter = calFrontFaceCenterY+cryYSize*(-0.5*calNCryY+0.5+iy);
  fZCenter = calFrontFaceCenterZ+0.5*cryZSize;

}

Crystal::~Crystal()
{;}

void Crystal::Print()
{
  cout<<fXi<<" "<<fYi<<" Status "<<fStatus<<" Energy "<<fEnergy<<" Charge "<<fCharge<<" Time "<<fTime<<endl;
}

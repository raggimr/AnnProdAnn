#ifndef Cluster_h
#define Cluster_h
#include "Histo.h"
#include "Crystal.h"

#define NMAXCRYSTALSINCLUSTER 150
class Cluster {

public :
  Cluster();
  ~Cluster();
  
 public :
  double GetRawEnergy()  {return fRawEnergy;};
  double GetEnergy()     {return fEnergy;};
  double GetTime()       {return fTime;};	

  double GetXCenter(){return fXCenter;};
  double GetYCenter(){return fYCenter;};

  int AddCrystal(Crystal *);

  void  Print();

 private:
  int fNCrystals;
  Crystal* fCrystalList[NMAXCRYSTALSINCLUSTER];
  double fRawEnergy;
  double fEnergy;
  double fTime;	 
  double fXCenter;	 
  double fYCenter;	 
};
#endif

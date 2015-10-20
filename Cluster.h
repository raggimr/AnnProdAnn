#ifndef Cluster_h
#define Cluster_h

#include "Crystal.h"

#define CLUSTER_N_MAX_CRYSTALS_IN_CLUSTER 150

class Cluster {

public :
  Cluster();
  ~Cluster();
  
 public :

  int AddCrystal(Crystal *); // Returns number of crystals currently in cluster

  double GetRawEnergy()  {return fRawEnergy;};
  double GetEnergy()     {return fEnergy;};
  double GetTime()       {return fTime;};
  double GeNCrystals()   {return fNCrystals;};	

  double GetXCenter(){return fXCenter;};
  double GetYCenter(){return fYCenter;};

  double ComputeTime();
  double ComputeEnergy();
  double ComputeCenter();

  void  Print();

 private:

  int fNCrystals;
  Crystal* fCrystalList[CLUSTER_N_MAX_CRYSTALS_IN_CLUSTER];
  double fRawEnergy;
  double fEnergy;
  double fTime;	 
  double fXCenter;	 
  double fYCenter;	 

};
#endif

#ifndef CrystalHandler_h
#define CrystalHandler_h

#include "Crystal.h"

#define CRYSTALHANDLER_N_MAX_CRYSTALS_X 30
#define CRYSTALHANDLER_N_MAX_CRYSTALS_Y 30

class CrystalHandler {

 public :
  CrystalHandler();
  ~CrystalHandler();
  
 public :

  int GetNCrystals(){return fNCrystals;};
  void SortEnergy();
  void Print();

  Crystal* GetSeed(double Ethr);

  Crystal* CreateCrystal(int ix,int iy);

  Crystal* GetCrystal(int x,int y);       //return pointer from crystal map
  Crystal* GetCrystal(int i);             //return pointer from sorted crystal array
  Crystal* GetCrystal(double x,double y); //return pointer from geometrical position of point

  // The following method is needed for multiple cluster finding on same event
  void ResetCrystals(); // Set status of all crystals to "not used"/"not seed"

 private:

  int fNCrystals; 

  Crystal* fCrystalMap[CRYSTALHANDLER_N_MAX_CRYSTALS_X][CRYSTALHANDLER_N_MAX_CRYSTALS_Y];
  Crystal* fCrystalList[CRYSTALHANDLER_N_MAX_CRYSTALS_X*CRYSTALHANDLER_N_MAX_CRYSTALS_Y];

  int fNCryX;
  int fNCryY;

};
#endif

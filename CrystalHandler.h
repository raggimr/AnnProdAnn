#ifndef CrystalHandler_h
#define CrystalHandler_h
#include "Histo.h"
#include "Crystal.h"

class CrystalHandler {

public :
  CrystalHandler();
  ~CrystalHandler();
  
 public :
  //  int FindSeeds(double thr); //returns Nseeds with E>thr

  int GetNCrystals(){return fNCrystals;};
  void SortEnergy();
  void Print();


  Crystal * GetSeed(double Ethr); //return pointer to crystal

  Crystal * CreateCrystal(int ix,int iy); //return pointer to crystal

  Crystal * GetCrystal(int x,int y); //return pointer from crystal map
  Crystal * GetCrystal(int i);      //return pointer from crystal array

  Crystal * GetCrystalFromPos(double x,double y); //return poiter to crystal

 private:
  Crystal * fCrystalMap[30][30];
  Crystal * fCrystalList[900]; //30*30 will be energy sorted 
  int fNCrystals; 
  //  int fOrderedList[900];
};
#endif

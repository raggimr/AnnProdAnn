#ifndef CompBG_h
#define CompBG_h
#include "Histo.h"
class CompBG {
 public :
  CompBG();
  ~CompBG();
  

  int GetNbAnn(){return NbAnn;};

  double GetBGMass(int k){return BGMass[k];};
  double GetBGMassVis(int k){return BGMassVis[k];};

  double GetBG3gMass(int k){return BG3gMass[k];};
  double GetBG3gMassVis(int k){return BG3gMassVis[k];};

  void CompBackG(char* ListBG,int nprim);
  void Comp3gBG(char* List3G,int nprim);

  double GetNtotE(){return NtotE;};
  
 private: 
  int BGMass[20];
  int BGMassVis[20];

  int BG3gMass[20];
  int BG3gMassVis[20];

  int NbAnn;
  int NBGVis;
  int NBG3gVis;
  float NtotE;
 private:
  Histo* his; 
};
#endif

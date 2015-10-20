#ifndef CompAcc_h
#define CompAcc_h
#include "Histo.h"

class CompAcc {
public :
  CompAcc();
  ~CompAcc();
  
  double CompAccVis(char* ListVis, int nacc);
  double CompAccInv(char* ListInv, int nacc);

  double GetAccInv(int Nacc) {return fAccInv;};
  double GetAccInvE(int Nacc){return fEAccInv;};

  double GetAccVis(int Nacc) {return fAccVis;};
  double GetAccVisE(int Nacc){return fEAccVis;};

  void FillMassRes();

public :

 private:
  Histo* his; 
  Double_t fAccInv;
  Double_t fEAccInv;

  Double_t fAccVis;
  Double_t fEAccVis;
  Double_t fNDP;
  Double_t fNDPVis;
};
#endif

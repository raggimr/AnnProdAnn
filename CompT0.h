#ifndef CompT0_h
#define CompT0_h
#include "Histo.h"
#include "GeomParam.h"

class CompT0 {
public :
  CompT0();
  ~CompT0();
  
  double DoT0(char* ListT0);
  double CheckT0(char* ListT0);
  //  double ApplyT0();
  double CorrectCellT(Double_t XCell, Double_t YCell);
  double CorrectSACT(Double_t XSAC, Double_t YSAC);
  double CorrectHitT(Int_t NLay);
  double CorrectTrackT(Double_t TrackP);
  double CorrectTrackEVeto(Double_t TrackP);
  
public :
  GeomParam* geo;

};
#endif

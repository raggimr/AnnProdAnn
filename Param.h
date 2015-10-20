#ifndef Param_h
#define Param_h
#include <iostream>
#include "cstdlib"
using namespace std;

class Param {
public :
  Param();
  ~Param();
  
  void InitParam();
  void InitCut();
  void WriteParam();
  double GetAnnCross(){return AnnCross;};
  double Get3gCross(){return tregCross;};
  double Get3gProb() {return tregProb;};
  double GetInvFlag(){return IsInvAnOn;};
  double GetVisFlag(){return IsVisAnOn;};
  double GetDoAcc()  {return IsDoAcc;};

  double GetIs3gOn() {return Is3gOn;};
  int   GetNMasses() {return NMasses;};
  double GetMinClRad() {return MinClRad;};
  double GetMaxClRad() {return MaxClRad;};

  double GetTWindInv() {return TWindInv;};
  double GetTWindVis() {return TWindVis;};

  double GetMinECl(int i)  {return MinClEne[i];};
  double GetMaxECl(int i)  {return MaxClEne[i];};
  double GetMeanMM2(int i) {return MeanMM2[i];};
  double GetRMSMM2(int i)  {return RMSMM2[i];};
  double GetUMass(int i)   {return UMass[i];};
  double GetsigmaUg(int i) {return sigmaUg[i];};
  double GetAnnProb()      {return AnnProb;};
  double GetTreGProb()      {return tregProb;};
  double GetDelta(int i)    {return Delta[i];};
  double GetDelta750(int i)    {return Delta750[i];};

private :
  float AnnCross;
  float tregCross;
  double AnnProb;
  double tregProb;
  float Dtarg;
  float IsInvAnOn;
  float IsVisAnOn;
  float IsDoAcc;
  float Is3gOn;
  int   NMasses;
  float TWindInv,TWindVis;
  float MinClRad,MaxClRad;
  double MinClEne[20];
  double MaxClEne[20];
  double MeanMM2[20];
  double RMSMM2[20];
  double UMass[20];
  double sigmaUg[20];
  double sigmaUg750[20];
  double Delta[20];
  double Delta750[20];
 public:
  static Param* GetInstance();
 private:
  static Param* fInstance;
  //  protected:
  //  Param();
};
#endif

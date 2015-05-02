#ifndef Crystal_h
#define Crystal_h
#include "Histo.h"

class Crystal {

public :
  Crystal(int ,int);
  ~Crystal();
  
 public :
  double GetEnergy()  {return fEnergy;};
  double GetTime()    {return fTime;};	
  double GetCharge()  {return fCharge;};

  double GetXCenter();
  double GetYCenter();

  int    GetXi()      {return fXi;};	
  int    GetYi()      {return fYi;};	
  int    IsUsed()     {return fUsed;};	
  int    IsSeed()     {return fSeed;};  

  double SetEnergy(double e)  {fEnergy=e;};
  double SetTime(double t)    {fTime=t;};	
  double SetCharge(double cha)  {fCharge=cha;};
  void    SetUsed()     {fUsed=1;};	
  void    ResetUsed()   {fUsed=0;};	
  void    SetSeed()     {fSeed=1;};  
  void    ResetSeed()   {fSeed=0;};
  void  Print();
 private:
  double fEnergy;
  double fTime;	 
  double fCharge;
  int fXi;	 
  int fYi;	 
  int fUsed;	 
  int fSeed;  
};
#endif

#ifndef Crystal_h
#define Crystal_h

#define CRYSTAL_STATUS_BIT_USED 0
#define CRYSTAL_STATUS_BIT_SEED 1

class Crystal {

 public :
 
  Crystal(int ,int);
  ~Crystal();
  
 public :

  double GetEnergy()  {return fEnergy;};
  double GetTime()    {return fTime;};	
  double GetCharge()  {return fCharge;};

  double SetEnergy(double e)   { fEnergy=e; };
  double SetTime(double t)     { fTime=t; };	
  double SetCharge(double cha) { fCharge=cha; };

  double GetXCenter() {return fXCenter;};
  double GetYCenter() {return fYCenter;};
  double GetZCenter() {return fZCenter;};

  int GetXi() {return fXi;};
  int GetYi() {return fYi;};

  bool IsUsed() {return fStatus & (1 << CRYSTAL_STATUS_BIT_USED);};
  bool IsSeed() {return fStatus & (1 << CRYSTAL_STATUS_BIT_SEED);};

  void SetUsed()   { fStatus |=  (1 << CRYSTAL_STATUS_BIT_USED); };
  void ResetUsed() { fStatus &= ~(1 << CRYSTAL_STATUS_BIT_USED); };
  void SetSeed()   { fStatus |=  (1 << CRYSTAL_STATUS_BIT_SEED); };
  void ResetSeed() { fStatus &= ~(1 << CRYSTAL_STATUS_BIT_SEED); };

  void  Print();

 private:

  int fXi;	 
  int fYi;

  int fStatus;

  double fXCenter;
  double fYCenter;
  double fZCenter;

  double fEnergy;
  double fTime;	 
  double fCharge;

};
#endif

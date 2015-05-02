#ifndef CompLim_h
#define CompLim_h

class CompLim {
public :
  CompLim();
  ~CompLim();
  
  double CompLimVis(double NBG, double Ngg,double Accgg,double AccUg,double Delta);
  double CompLimInv(double NBG, double Ngg,double Accgg,double AccUg,double Delta);

public :

};
#endif

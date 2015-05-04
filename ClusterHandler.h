#ifndef ClusterHandler_h
#define ClusterHandler_h
#include "Histo.h"
#include "Cluster.h"
#define NMAXCLUSTERS 20
class ClusterHandler {

public :
  ClusterHandler();
  ~ClusterHandler();
  
 public :
  //  int FindSeeds(double thr); //returns Nseeds with E>thr

  int GetNClusters(){return fNClusters;};
  void SortEnergy();
  void Print();

  Cluster * GetCluster(int );  //return pointer from cluster
  Cluster * NewCluster();      //Create a new cluster and return pointer

 private:
  Cluster * fClusterList[NMAXCLUSTERS];
  int fNClusters; 
};
#endif

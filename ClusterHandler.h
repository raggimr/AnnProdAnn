#ifndef ClusterHandler_h
#define ClusterHandler_h

#include "Cluster.h"

#define CLUSTERHANDLER_N_MAX_CLUSTERS 20

class ClusterHandler {

 public :

  ClusterHandler();
  ~ClusterHandler();
  
 public :

  int GetNClusters(){return fNClusters;};
  void Print();

  Cluster* NewCluster(); //Create a new cluster and return pointer
  Cluster* GetCluster(int);

  // Erase results from previous cluster findings
  void ResetClusters();

 private:

  int fNClusters; 
  Cluster * fClusterList[CLUSTERHANDLER_N_MAX_CLUSTERS];

};
#endif

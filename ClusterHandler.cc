#include "ClusterHandler.h"

#include <iostream>
#include "cstdlib"
#include "math.h"

using namespace std;

//Costruttore
ClusterHandler::ClusterHandler()
{
  fNClusters=0;
}

ClusterHandler::~ClusterHandler()
{
  ResetClusters();
}

void ClusterHandler::ResetClusters()
{
  // Kill all existing clusters and reset counter
  for(int kk; kk<fNClusters;kk++){
    delete fClusterList[kk];
  }
  fNClusters = 0;
}

Cluster* ClusterHandler::NewCluster()
{
  if(fNClusters<CLUSTERHANDLER_N_MAX_CLUSTERS){
    Cluster * clu = new Cluster();
    fClusterList[fNClusters++]=clu;
    return clu;
  } else {
    cout<<"WARNING - ClusterHandler::NewCluster - Too many clusters in event: "<<fNClusters<<endl;
    return 0;
  }
}

Cluster* ClusterHandler::GetCluster(int i)
{
  if (i<0 || i>=fNClusters) {
    cout<<"WARNING - ClusterHandler::GetCluster - Attept to access cluster outside list: "<<i<<endl;
    return 0;
  }
  return fClusterList[i];
}

void ClusterHandler::Print()
{
  cout<<"I know "<<fNClusters<<" Clusters "<<endl;
  for(int kk=0;kk<fNClusters;kk++){
    fClusterList[kk]->Print();
  }
}

#include <algorithm>
#include "ClusterHandler.h"
#include "Histo.h"

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
  // Kill all pointers to the cluster of the event
  for(int kk; kk<fNClusters;kk++){
    delete fClusterList[kk];
  }
}

Cluster* ClusterHandler::NewCluster()
{
  Cluster * clu = new Cluster();
  fClusterList[fNClusters++]=clu;
  return clu;
}

Cluster* ClusterHandler::GetCluster(int i)
{
  if(i>=0 && i<fNClusters) return fClusterList[i];
  return 0;
}

void ClusterHandler::Print()
{
  cout<<"I know "<<fNClusters<<" Clusters "<<endl;
  for(int kk=0;kk<fNClusters;kk++){
    fClusterList[kk]->Print();
  }
}

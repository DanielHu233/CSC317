#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>

typedef struct hashValue{
  int f1;
  int f2;
  int v1;
  int v2;
}hashVal;

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  //first define base case
  if(num_iters == 0) return;
  
  //need a container that holds edge informations
  int numEdge = V.rows() + F.rows() - 2;

  //**********create a hash table(linear hashing), *********key is the sum of indices of the two vertices*********
  std::vector<std::pair<int, hashVal> > edges;
  edges.resize(numEdge);
  for(int i = 0;i < edges.size();i++){
    edges[i].first = -1;
    edges[i].second.f1 = -1;
    edges[i].second.f2 = -1;
  }
  for(int i = 0;i < F.rows();i++){
    //deal with the first three edges of this surface(fill in face indices)
    for(int j = 0;j < F.cols()-1;j++){
      //if not dealt with before
      if(edges[F(i, j) + F(i, j+1)].first < 1){
        edges[F(i, j) + F(i, j+1)].first += 1;
        if(edges[F(i, j) + F(i, j+1)].second.f1 == -1){
          edges[F(i, j) + F(i, j+1)].second.f1 = i;
        }else{
          edges[F(i, j) + F(i, j+1)].second.f2 = i;
        }
      }
    }
    //deal with the fourth edge of this surface(fill in face indices)
    if(edges[F(i, 3) + F(i, 0)].first < 1){
      edges[F(i, 3) + F(i, 0)].first += 1;
      if(edges[F(i, 3) + F(i, 0)].second.f1 == -1){
        edges[F(i, 3) + F(i, 0)].second.f1 = i;
      }else{
        edges[F(i, 3) + F(i, 0)].second.f2 = i;
      }
    }
    //fill in vertices indices of this edge
    for(int j = 0;j < F.cols()-1;j++){
      edges[F(i, 3) + F(i, 0)].second.v1 = F(i, j);
      edges[F(i, 3) + F(i, 0)].second.v2 = F(i, j+1);
    }
    edges[F(i, 3) + F(i, 0)].second.v1 = F(i, 3);
    edges[F(i, 3) + F(i, 0)].second.v2 = F(i, 0);
  }
  //********  CREATION DONE  ****************************************************************************

  //for each face, add a face point
  Eigen::MatrixXd faceMid;
  faceMid.resize(F.rows(), 3);//********************container that holds face point infos****************
  for(int i = 0;i < F.rows();i++){
    Eigen::RowVector3d mid(0, 0, 0);
    for(int j = 0;j < F.cols();j++){
      mid(0) += V(F(i, j), 0) / 4;
      mid(1) += V(F(i, j), 1) / 4;
      mid(2) += V(F(i, j), 2) / 4;
    }
    faceMid.row(i) = mid;//fill in 
  }

  //for each edges, add an edge point
  Eigen::MatrixXd edgeMid;
  edgeMid.resize(numEdge, 3);//********************container that holds edge point infos****************
  for(int i = 0;i < numEdge;i++){
    Eigen::RowVector3d mid(0, 0, 0);
    //counts in face points
    mid(0) += faceMid(edges[i].second.f1, 0) / 4;
    mid(1) += faceMid(edges[i].second.f1, 1) / 4;
    mid(2) += faceMid(edges[i].second.f1, 2) / 4;

    mid(0) += faceMid(edges[i].second.f2, 0) / 4;
    mid(1) += faceMid(edges[i].second.f2, 1) / 4;
    mid(2) += faceMid(edges[i].second.f2, 2) / 4;
    
    //counts in vertices
    mid(0) += V(edges[i].second.v1, 0) / 4;
    mid(1) += V(edges[i].second.v1, 1) / 4;
    mid(2) += V(edges[i].second.v1, 2) / 4;

    mid(0) += V(edges[i].second.v2, 0) / 4;
    mid(1) += V(edges[i].second.v2, 1) / 4;
    mid(2) += V(edges[i].second.v2, 2) / 4;

    edgeMid.row(i) = mid;//fill in 
  }

  //move old vertices to new positions
  Eigen::MatrixXd newvertices;//********************container that holds new vertices positions****************
  newvertices.resize(V.rows(), 3);
  for(int i = 0;i < V.rows();i++){
    Eigen::RowVector3d newPos(0, 0, 0);
    for(int j = 0;j < numEdge;j++){
      if(edges[j].second.v1 == i || edges[j].second.v2 == i){
        //find the vertex in edge, so now know edgemid and facemids
        int edgeIndex = i;
        if(edges[j].second.v1 == i){
          edgeIndex += edges[j].second.v2;
        }else{
          edgeIndex += edges[j].second.v1;
        }

        newPos(0) += faceMid(edgeIndex, 0) / 6 / 3;//F/n, since face point will be counted twice
        newPos(1) += faceMid(edgeIndex, 1) / 6 / 3;
        newPos(2) += faceMid(edgeIndex, 2) / 6 / 3;
        newPos(0) += edgeMid(edgeIndex, 0) / 3 * 2 / 3;//2R/n
        newPos(1) += edgeMid(edgeIndex, 1) / 3 * 2 / 3;
        newPos(2) += edgeMid(edgeIndex, 2) / 3 * 2 / 3;
      }
    }
    newvertices.row(i) = newPos;
  }

  //now, build up SV
  int newVnum = V.rows() + edgeMid.rows() + faceMid.rows();
  int newFnum = F.rows() * 4;
  SV.resize(newVnum, 3);
  SF.resize(newFnum, 4);

  for(int i = 0;i < numEdge;i++){
    SV(i, 0) = edgeMid(i, 0);
    SV(i, 1) = edgeMid(i, 1);
    SV(i, 2) = edgeMid(i, 2);
  }
  for(int i = 0;i < F.rows();i++){
    SV(i + numEdge, 0) = faceMid(i, 0);
    SV(i + numEdge, 1) = faceMid(i, 1);
    SV(i + numEdge, 2) = faceMid(i, 2);
  }
  for(int i = 0;i < V.rows();i++){
    SV(i + numEdge + F.rows(), 0) = newvertices(i, 0);
    SV(i + numEdge + F.rows(), 1) = newvertices(i, 1);
    SV(i + numEdge + F.rows(), 2) = newvertices(i, 2);
  }
  
  //*********************do not know how to implement face connections***************************************
  /*for(int i = 0;i < numEdge;i++){
    //each face now turns into 4 faces
    
  }*/
  SF = F;
  //recursive call
  Eigen::MatrixXd newSV;
  Eigen::MatrixXi newSF;
  catmull_clark(SV, SF, num_iters-1, newSV, newSF);
  ////////////////////////////////////////////////////////////////////////////
}

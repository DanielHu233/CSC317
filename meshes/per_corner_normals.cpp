#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include "cmath"

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  //first find adjacent faces
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  //now loop through faces
  for(int i = 0;i < F.rows();i++){
    //the reference normal direction
    Eigen::RowVector3d reference = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
    
    for(int j = 0;j < F.cols();j++){
      //loop through VF for all faces
      for(int k = 0;k < VF[F(i,j)].size();k++){
        //normal of adjacent faces
        Eigen::RowVector3d faceNorm = triangle_area_normal(V.row(F(VF[F(i, j)][k], 0)), 
                                  V.row(F(VF[F(i, j)][k], 1)),
                                  V.row(F(VF[F(i, j)][k], 2)));
        
        //if in accepted range
        if((faceNorm.dot(reference) / (faceNorm.norm() * reference.norm())) > cos(corner_threshold / 180 * M_PI)){
          N(3 * i + j, 0) += faceNorm(0);
          N(3 * i + j, 1) += faceNorm(1);
          N(3 * i + j, 2) += faceNorm(2);
        }
      } 
      //finally normalize
      N.row(3 * i + j).normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

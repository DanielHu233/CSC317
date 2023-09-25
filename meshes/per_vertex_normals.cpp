#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  //loop through all vertices
  for(int i = 0;i < V.rows();i++){
    Eigen::RowVector3d total(0, 0, 0);
    //calculate weighted sum of all corresponding surfaces
    for(int j = 0;j < F.rows();j++){
      //find an adjacent surface
      if((F(j, 0) == i) || (F(j, 1) == i) || (F(j,2) == i)){
        total += triangle_area_normal(V.row(F(j, 0)), V.row(F(j, 1)), V.row(F(j, 2)));
      }
    }
    N.row(i) = total.normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}

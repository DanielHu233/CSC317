#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  N.resize(F.rows(), 3);
  //loop through each row of F(per face)
  for(int i = 0;i < F.rows();i++){
    N.row(i) = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
    N.row(i).normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}

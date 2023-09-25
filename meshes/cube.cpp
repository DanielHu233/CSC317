#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  //vertices
  V.resize(8,3);
  V.row(0) = Eigen::RowVector3d(0, 0, 0);
  V.row(1) = Eigen::RowVector3d(0, 0, 1);
  V.row(2) = Eigen::RowVector3d(1, 0, 1);
  V.row(3) = Eigen::RowVector3d(1, 0, 0);
  V.row(4) = Eigen::RowVector3d(1, 1, 0);
  V.row(5) = Eigen::RowVector3d(1, 1, 1);
  V.row(6) = Eigen::RowVector3d(0, 1, 1);
  V.row(7) = Eigen::RowVector3d(0, 1, 0);
  //faces
  F.resize(6,4);
  F.row(0) = Eigen::RowVector4i(1, 4, 3, 2);
  F.row(1) = Eigen::RowVector4i(2, 3, 6, 7);
  F.row(2) = Eigen::RowVector4i(5, 8, 7, 6);
  F.row(3) = Eigen::RowVector4i(1, 8, 5, 4);
  F.row(4) = Eigen::RowVector4i(1, 2, 7, 8);
  F.row(5) = Eigen::RowVector4i(3, 4, 5, 6);
  //texture map corners
  UV.resize(14,2);
  UV.row(0) = Eigen::RowVector2d(0.25, 0.00);
  UV.row(1) = Eigen::RowVector2d(0.50, 0.00);
  UV.row(2) = Eigen::RowVector2d(0.00, 0.25);
  UV.row(3) = Eigen::RowVector2d(0.25, 0.25);
  UV.row(4) = Eigen::RowVector2d(0.50, 0.25);
  UV.row(5) = Eigen::RowVector2d(0.75, 0.25);
  UV.row(6) = Eigen::RowVector2d(1.00, 0.25);
  UV.row(7) = Eigen::RowVector2d(0.00, 0.50);
  UV.row(8) = Eigen::RowVector2d(0.25, 0.50);
  UV.row(9) = Eigen::RowVector2d(0.50, 0.50);
  UV.row(10) = Eigen::RowVector2d(0.75, 0.50);
  UV.row(11) = Eigen::RowVector2d(1.00, 0.50);
  UV.row(12) = Eigen::RowVector2d(0.25, 0.75);
  UV.row(13) = Eigen::RowVector2d(0.50, 0.75);
  //face texture
  UF.resize(6,4);
  UF.row(0) = Eigen::RowVector4i(3, 4, 9, 8);
  UF.row(1) = Eigen::RowVector4i(4, 5, 10, 9);
  UF.row(2) = Eigen::RowVector4i(5, 6, 11, 10);
  UF.row(3) = Eigen::RowVector4i(6, 7, 12, 11);
  UF.row(4) = Eigen::RowVector4i(9, 10, 14, 13);
  UF.row(5) = Eigen::RowVector4i(1, 2, 5, 4);
  //define normal vectors
  NV.resize(6,3);
  NV.row(0) = Eigen::RowVector3d(0, -1, 0);
  NV.row(1) = Eigen::RowVector3d(0, 0, 1);
  NV.row(2) = Eigen::RowVector3d(0, 1, 0);
  NV.row(3) = Eigen::RowVector3d(0, 0, -1);
  NV.row(4) = Eigen::RowVector3d(-1, 0, 0);
  NV.row(5) = Eigen::RowVector3d(1, 0, 0);
  //face vertices normals
  NF.resize(6,4);
  NF.row(0) = Eigen::RowVector4i(1, 1, 1, 1);
  NF.row(1) = Eigen::RowVector4i(2, 2, 2, 2);
  NF.row(2) = Eigen::RowVector4i(3, 3, 3, 3);
  NF.row(3) = Eigen::RowVector4i(4, 4, 4, 4);
  NF.row(4) = Eigen::RowVector4i(5, 5, 5, 5);
  NF.row(5) = Eigen::RowVector4i(6, 6, 6, 6);
}

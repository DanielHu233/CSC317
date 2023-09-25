#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double x1 = xzx[0];
  double z = xzx[1];
  double x2 = xzx[2];
  Eigen::Affine3d X1, Z, X2;
  X1.matrix() <<
    1,0,0,0,
    0, cos(x1 * M_PI / 180.0), -sin(x1 * M_PI / 180.0),0,
    0, sin(x1 * M_PI / 180.0), cos(x1 * M_PI / 180.0),0,
    0,0,0,1;
  Z.matrix() << 
    cos(z * M_PI / 180.0), -sin(z * M_PI / 180.0),0,0,
    sin(z * M_PI / 180.0), cos(z * M_PI / 180.0),0,0,
    0,0,1,0,
    0,0,0,1;
  X2.matrix() << 
    1,0,0,0,
    0, cos(x2 * M_PI / 180.0), -sin(x2 * M_PI / 180.0),0,
    0, sin(x2 * M_PI / 180.0), cos(x2 * M_PI / 180.0),0,
    0,0,0,1;
  return X1 * Z * X2;
  /////////////////////////////////////////////////////////////////////////////
}

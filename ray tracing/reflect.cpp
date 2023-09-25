#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  //r=d−2(d⋅n)n, where r is the output ray direction
  Eigen::Vector3d r = in - 2 * (in.dot(n)) * n;
  r = r.normalized();
  return r;
  ////////////////////////////////////////////////////////////////////////////
}

#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double sigma = max_step;
  Eigen::VectorXd znew;
  do{
    znew = z - sigma * dz;
    proj_z(znew);
    sigma /= 2;
  }while(f(z) < f(znew));
  return sigma;
  /////////////////////////////////////////////////////////////////////////////
}

#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int sigma = 20000;
  Eigen::VectorXd gradient;
  for(int i = 0;i < max_iters;i++){
    gradient = grad_f(z); 
    z = z - line_search(f, proj_z, z, gradient, sigma) * gradient;
    proj_z(z);
  }
  /////////////////////////////////////////////////////////////////////////////
}

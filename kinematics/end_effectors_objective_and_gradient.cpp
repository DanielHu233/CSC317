#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tip_pos = transformed_tips(copy, b);
    //E(Xb) = ||Xb - q||^2
    double result = (xb0 - tip_pos).squaredNorm();
    return result;
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tip_pos = transformed_tips(copy, b);
    Eigen::MatrixXd jacobian;
    kinematics_jacobian(copy, b, jacobian);

    Eigen::VectorXd result = Eigen::VectorXd::Zero(A.size());
    for(int i = 0;i < b.size();i++){
      double dEdx0 = 2 * (tip_pos[3 * i + 0] - xb0[3 * i + 0]);
      result += jacobian.row(3 * i + 0).transpose() * dEdx0;
      double dEdx1 = 2 * (tip_pos[3 * i + 1] - xb0[3 * i + 1]);
      result += jacobian.row(3 * i + 1).transpose() * dEdx1;
      double dEdx2 = 2 * (tip_pos[3 * i + 2] - xb0[3 * i + 2]);
      result += jacobian.row(3 * i + 2).transpose() * dEdx2;
    }
    return result;
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    for(int i = 0;i < skeleton.size();i++){
      A[3 * i + 0] = std::max(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[3 * i + 0]));
      A[3 * i + 1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[3 * i + 1]));
      A[3 * i + 2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[3 * i + 2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}

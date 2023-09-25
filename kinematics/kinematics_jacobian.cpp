#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  Eigen::VectorXd tip_pos = transformed_tips(skeleton, b);

  //J(i*3+c,j*3+a) = ∂xi,c/∂θj
  for(int i = 0;i < skeleton.size();i++){
    for(int j = 0;j < 3;j++){
      Skeleton copy = skeleton;
      copy[i].xzx[j] += 1.0e-7;
      Eigen::VectorXd newpos = transformed_tips(copy, b);
      Eigen::VectorXd dx = newpos - tip_pos;
      for(int k = 0;k < J.rows();k++){
        J(k, 3 * i + j) = dx[k] / 1.0e-7;
      }
    }
  } 
  /////////////////////////////////////////////////////////////////////////////
}

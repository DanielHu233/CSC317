#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd result(3 * b.rows());
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > Transformation;
  forward_kinematics(skeleton, Transformation);

  for(int i = 0;i < b.rows();i++){
  	Eigen::Vector4d tip = skeleton[b[i]].rest_T * Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);
  	Eigen::Vector4d Tip = Transformation[b[i]] * tip;
  	result[3 * i] = Tip[0];
  	result[3 * i + 1] = Tip[1];
  	result[3 * i + 2] = Tip[2];
  }
  return result;
  /////////////////////////////////////////////////////////////////////////////
}

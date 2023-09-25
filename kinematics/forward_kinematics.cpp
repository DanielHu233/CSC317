#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

Eigen::Affine3d recursive(const Skeleton & skeleton, int index){
  if(index == -1){
    //root, base case
    return Eigen::Affine3d::Identity();
  }else{
    //recursion
    Eigen::Affine3d parent_transformation = recursive(skeleton, skeleton[index].parent_index);
    Eigen::Affine3d rotation = euler_angles_to_transform(skeleton[index].xzx);
    //rest bone space * rotation * rest bone space^-1
    return parent_transformation * skeleton[index].rest_T * rotation * (skeleton[index].rest_T.inverse());
  }
}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for(int i = 0;i < skeleton.size();i++){
    T[i] = recursive(skeleton, i);
  }
  /////////////////////////////////////////////////////////////////////////////
}

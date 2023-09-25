#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  double min_d = std::numeric_limits<double>::infinity();
  sqrD = std::numeric_limits<double>::infinity();
  I = -1;
  //now find for closest
  for(int i = 0;i < points.rows();i++){
    min_d = (points.row(i) - query).squaredNorm();
    //update
    if (min_d < sqrD){
      sqrD = min_d;
      I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

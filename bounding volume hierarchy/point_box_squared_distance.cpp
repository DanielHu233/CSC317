#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  //check if x, y, z of the query is within th bound of the box
  double xlen = fmax(box.min_corner(0) - query(0), query(0) - box.max_corner(0));
  double ylen = fmax(box.min_corner(1) - query(1), query(1) - box.max_corner(1));
  double zlen = fmax(box.min_corner(2) - query(2), query(2) - box.max_corner(2));

  //calculate min distance
  double distance = 0;
  if(xlen > 0){
    distance += pow(xlen, 2);
  }
  if(ylen > 0){
    distance += pow(ylen, 2);
  }
  if(zlen > 0){
    distance += pow(zlen, 2);
  }
  return distance;
  ////////////////////////////////////////////////////////////////////////////
}

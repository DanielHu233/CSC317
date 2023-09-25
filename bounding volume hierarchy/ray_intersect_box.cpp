#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  //first find min max t for x, y, z direction of the box
  double min_x = box.min_corner(0);
  double min_y = box.min_corner(1);
  double min_z = box.min_corner(2);
  double max_x = box.max_corner(0);
  double max_y = box.max_corner(1);
  double max_z = box.max_corner(2);

  double min_x_t = (min_x - ray.origin(0)) / ray.direction(0);
  double max_x_t = (max_x - ray.origin(0)) / ray.direction(0);
  double min_y_t = (min_y - ray.origin(1)) / ray.direction(1);
  double max_y_t = (max_y - ray.origin(1)) / ray.direction(1);
  double min_z_t = (min_z - ray.origin(2)) / ray.direction(2);
  double max_z_t = (max_z - ray.origin(2)) / ray.direction(2);

  //adjust for positive and negative xyz
  if(ray.direction(0) < 0){
    double temp = min_x_t;
    min_x_t = max_x_t;
    max_x_t = temp;
  }
  if(ray.direction(1) < 0){
    double temp = min_y_t;
    min_y_t = max_y_t;
    max_y_t = temp;
  }
  if(ray.direction(2) < 0){
    double temp = min_z_t;
    min_z_t = max_z_t;
    max_z_t = temp;
  }

  //then find max of mins and min of maxs
  double max_of_min_t = fmax(fmax(min_x_t, min_y_t), min_z_t);
  double min_of_max_t = fmin(fmin(max_x_t, max_y_t), max_z_t);

  if(max_of_min_t <= min_of_max_t && min_of_max_t <= max_t){
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //since this time function is first order, calculate t directly
  double T = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
  if(T >= min_t && T < INFINITY){
    //hit exists and is not too close
    t = T;
    n = normal / normal.norm();
    return true;
  }else{
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}


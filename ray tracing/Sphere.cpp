#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //first calculate A B C in the quadratic equation driven from |p - c|^2 = r^2
  double A = ray.direction.dot(ray.direction);
  double B = 2 * ray.origin.dot(ray.direction) - 2 * ray.direction.dot(center);
  double C = ray.origin.dot(ray.origin) - 2 * ray.origin.dot(center) + center.dot(center) - radius * radius;

  //then, solve the quadratic equation 
  if(B*B - 4*A*C < 0){
    //hit point does not exist
    return false;
  }else{
    //there's one or two hit points
    double sqr = sqrt(B*B - 4*A*C);
    double t1 = (-1*B + sqr) / (2*A);
    double t2 = (-1*B - sqr) / (2*A);
    if(fmin(t1, t2) >= min_t){
      //larger than the min distance
      t = fmin(t1, t2);
      //normal is (X - c)/r
      n = (ray.origin + t * ray.direction - center) / radius;
      return true;
    }else if(fmax(t1, t2) >= min_t){
      t = fmax(t1, t2);
      //normal is (X - c)/r
      n = (ray.origin + t * ray.direction - center) / radius;
      return true;
    }else{
      //hit point too close to camera
      return false;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


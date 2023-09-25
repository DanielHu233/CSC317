#include "Triangle.h"
#include "Ray.h"
#include <tuple>
#include <string>
#include <iostream>
#include <Eigen/Geometry>
using namespace std;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //first determine the plane the triangle lies in and find hit point on that plane to get t
  Eigen::Vector3d a = get<0>(corners);
  Eigen::Vector3d b = get<1>(corners);
  Eigen::Vector3d c = get<2>(corners);

  Eigen::Vector3d normal = (b - a).cross(c - a);
  double T = (a - ray.origin).dot(normal) / ray.direction.dot(normal);
  if(T >= min_t && T < INFINITY){
    //hit exists on plane, determine if falls in the triangle
    Eigen::Vector3d hitpoint = ray.origin + T * ray.direction;
    //the parameters in the equations
    double a1 = (b - a)[0];
    double a2 = (c - a)[0];
    double a3 = a[0];
    double a4 = hitpoint[0];
    double b1 = (b - a)[1];
    double b2 = (c - a)[1];
    double b3 = a[1];
    double b4 = hitpoint[1];

    double gama = (b4 - b3 - (a4 - a3)*b1/a1) / (b2 - (a2*b1/a1));
    double beta = (a4 - a3 - gama * a2) / a1;
    //check if lies in triangle
    if(beta >= 0 && gama >= 0 && beta + gama <= 1){
      //lies in
      t = T;
      n = normal / normal.norm();
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}



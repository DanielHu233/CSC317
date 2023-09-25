#include "viewing_ray.h"
#include <iostream>

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  //ray's origin is e
  ray.origin = camera.e;

  //ray's direction is s-e
  //first compute width and height of a pixel
  double pixwidth = camera.width / (double)width;
  double pixheight = camera.height / (double)height;

  //then, calculate s
  Eigen::Vector3d center = camera.e + camera.d*(-1*camera.w);
  int i_deviation = height / 2 - i;  //notice width and height are even numbers
  int j_deviation = j - width / 2;

  Eigen::Vector3d deltaV = camera.v * (i_deviation - 0.5) * pixheight;
  Eigen::Vector3d deltaU = camera.u * (j_deviation + 0.5) * pixwidth;
  
  Eigen::Vector3d s = center + deltaU + deltaV;

  //finally calculate direction s-e
  ray.direction = s - camera.e;
  ////////////////////////////////////////////////////////////////////////////
}


#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  //we can assume triangles are not co planar
  //treat each edges of the triangles as rays to see if the ray intersect with the other triangle
  Ray a1(A0, A1 - A0);
  Ray a2(A0, A2 - A0);
  Ray a3(A1, A2 - A1);
  Ray b1(B0, B1 - B0);
  Ray b2(B0, B2 - B0);
  Ray b3(B1, B2 - B1);

  double t = 0;
  bool intersect = ray_intersect_triangle(a1, B0, B1, B2,
   0, 1, t) ||
   ray_intersect_triangle(a2, B0, B1, B2,
   0, 1, t) ||
   ray_intersect_triangle(a3, B0, B1, B2,
   0, 1, t) ||
   ray_intersect_triangle(b1, A0, A1, A2,
   0, 1, t) ||
   ray_intersect_triangle(b2, A0, A1, A2,
   0, 1, t) ||
   ray_intersect_triangle(b3, A0, A1, A2,
   0, 1, t);

  if(intersect) return true;
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  //just call first hit fuction
  int hit_id = -1;
  return first_hit(ray, min_t, triangles, hit_id, t, n);
  ////////////////////////////////////////////////////////////////////////////
}




#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  hit_t = std::numeric_limits<double>::infinity();
  double min_hit_t;

  // check intersect and record smallest t value
  bool hit = false;
  Eigen::RowVector3d A, B, C;
  for (int i = 0;i < F.rows();i++){
    //get vertices
    A = V.row(F(i,0));
    B = V.row(F(i,1));
    C = V.row(F(i,2));

    if(ray_intersect_triangle(ray, A, B, C, min_t, max_t, min_hit_t)){ 
      //update
      if (min_hit_t < hit_t){
        hit = true;
        hit_t = min_hit_t;
        hit_f = i;
      }
    }
  }
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

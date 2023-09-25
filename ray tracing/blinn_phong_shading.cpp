#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,

  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  //first add ambient colour
  Eigen::Vector3d RGB = 0.1 * objects[hit_id]->material->ka; //Ia is set to 0.1

  //then, for each lights, check if shadowed
  for(int i = 0;i < lights.size();i++){
    //casting a ray from q+tl where q is the point of intersection and l is the direction of light. 
    Eigen::Vector3d q = ray.origin + ray.direction * t;
    Ray shadow_checker;
    shadow_checker.origin = q; //the origin of this tester light ray
    double max_t = -1;
    lights[i]->direction(q, shadow_checker.direction, max_t); //computes direction towards light, 
    //this is also the direction of this light

    //now call first hit
    int testing_id = -1;
    double hit_t = -1;
    Eigen::Vector3d normal;
    if(!first_hit(shadow_checker, 0.000001, objects, testing_id, hit_t, normal) || hit_t > max_t){ //allows a minimum t of 0.00001
      //now, no shadowing effect, can add diffuse and specular colors
      //diffuse color
      double diffuse_index = fmax(0, n.dot(shadow_checker.direction));
      RGB += diffuse_index * (lights[i]->I.array() * objects[hit_id]->material->kd.array()).matrix(); 

      //specular color
      Eigen::Vector3d h = (-ray.direction.normalized() + shadow_checker.direction).normalized();
      double specular_index = std::pow(fmax(0, n.dot(h)), objects[hit_id]->material->phong_exponent);
      RGB += specular_index * (lights[i]->I.array() * objects[hit_id]->material->ks.array()).matrix();
    }
  }

  return RGB;
  ////////////////////////////////////////////////////////////////////////////
}

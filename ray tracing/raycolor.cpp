#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

//this is the recursion helper for the raycolor function, it returns eigen not bool
Eigen::Vector3d color_helper(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d rgb){
  //the recursive helper function
  //first call first hit to get normal, id, t
  int id = -1;
  double t = -1;
  Eigen::Vector3d n;

  //base case 1, check if finds a hit
  if(first_hit(ray, min_t, objects, id, t, n)){
    //if hit, adds the color of this hit
    rgb = blinn_phong_shading(ray, id, t, n, objects, lights);

    //base case 2, check if reaches the max bouncing time
    if(num_recursive_calls < 30){ //max bounce time sets to 30
      Eigen::Vector3d reflected = reflect(ray.direction, n);
      Ray reflected_ray;
      reflected_ray.origin = ray.origin + t * ray.direction;
      reflected_ray.direction = reflected;
      Eigen::Vector3d rgb_new(0,0,0);
      rgb += (objects[id]->material->km.array() * 
      color_helper(reflected_ray, 0.000001, objects, lights, num_recursive_calls + 1, rgb_new).array()).matrix();
    }
  }
  return rgb;
}


bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  rgb = color_helper(ray, min_t, objects, lights, num_recursive_calls, rgb);
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

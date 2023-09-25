#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  int id = -1;
  double t_min = INT_MAX;
  Eigen::Vector3d normal;

  for(int i = 0;i < objects.size();i++){
    if(objects[i]->intersect(ray, min_t, t, n)){
      //intersection found and is closer
      if(t < t_min){
        t_min = t;
        id = i;
        normal = n;
      }
    }
  }

  if(id == -1){
    //not hit any of the object
    return false;
  }else{
    hit_id = id;
    t = t_min;
    n = normal;
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}


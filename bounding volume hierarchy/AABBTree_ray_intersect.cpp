#include "AABBTree.h"
// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  if(!ray_intersect_box(ray, this->box, min_t, max_t)){
    //does not hit the bounding box
    descendant = nullptr;
    return false;
  }else{
    //check if hit left or right childs' bounding box
    double tl = std::numeric_limits<double>::infinity();
    double tr = std::numeric_limits<double>::infinity();
    bool left_hit = false;
    bool right_hit = false;
    std::shared_ptr<Object> left_de;
    std::shared_ptr<Object> right_de;

    //recurse
    if(left){
      left_hit = left->ray_intersect(ray, min_t, max_t, tl, left_de);
    }
    if(right){
      right_hit = right->ray_intersect(ray, min_t, max_t, tr, right_de);
    }

    //when actual hit with an object
    if(!left_de && left_hit){
      left_de = left;
    }
    if(!right_de && right_hit){
      right_de = right;
    }

    if(left_hit && right_hit){
      //choose the minimum among the two hits
      t = fmin(tl, tr);
      if(tl <= tr){
        //pass the descendant up layer by layer
        descendant = left_de;
      }else{
        descendant = right_de;
      }
      return true;
    }else if(left_hit){
      t = tl;
      descendant = left_de;
      return true;
    }else if(right_hit){
      t = tr;
      descendant = right_de;
      return true;
    }else{
      return false;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  int object_num = objects.size();
  right = nullptr;
  left = nullptr;
  num_leaves = 0;
  //1 object
  if(object_num == 1){
    left = objects[0];
    right = nullptr;
    insert_box_into_box(objects[0]->box, box);
    num_leaves = 1;
    return;
  }else if(object_num == 2){
  //2 objects
    left = objects[0];
    right = objects[1];
    insert_box_into_box(objects[0]->box, box);
    insert_box_into_box(objects[1]->box, box);
    num_leaves = 2;
    return;
  }else{
  //more than 2 objects
    //first determine the longest axis
    for(int i = 0;i < object_num;i++){
      insert_box_into_box(objects[i]->box, box); //insert in all boxes of these objects 
    }
    double x_length = box.max_corner(0) - box.min_corner(0);
    double y_length = box.max_corner(1) - box.min_corner(1);
    double z_length = box.max_corner(2) - box.min_corner(2);
    
    //now start splitting objects into left and right groups
    std::vector<std::shared_ptr<Object> > lobjects;
    std::vector<std::shared_ptr<Object> > robjects;
    if(x_length >= y_length && x_length >= z_length){
      //split along x axis
      for (int i = 0;i < object_num;i++){
        if (objects[i]->box.center()(0) <= box.center()(0)) lobjects.push_back(objects[i]);
        else robjects.push_back(objects[i]);
      }
    }else if(y_length >= x_length && y_length >= z_length){
      //split along y axis
      for (int i = 0;i < object_num;i++){
        if (objects[i]->box.center()(1) <= box.center()(1)) lobjects.push_back(objects[i]);
        else robjects.push_back(objects[i]);
      }
    }else{
      //split along z axis
      for (int i = 0;i < object_num;i++){
        if (objects[i]->box.center()(2) <= box.center()(2)) lobjects.push_back(objects[i]);
        else robjects.push_back(objects[i]);
      }
    }

    //edge case where one side has got nothing, avoid infinite loop
    if(lobjects.size() == 0 && robjects.size() >= 2){
      std::shared_ptr<Object> change = robjects.back();
      robjects.pop_back();
      lobjects.push_back(change);
    }
    if(robjects.size() == 0 && lobjects.size() >= 2){
      std::shared_ptr<Object> change = lobjects.back();
      lobjects.pop_back();
      robjects.push_back(change);
    }
    num_leaves = object_num;

    //now do the recursive call
    left = std::make_shared<AABBTree>(lobjects, depth+1);
    right = std::make_shared<AABBTree>(robjects, depth+1);
  }
  ////////////////////////////////////////////////////////////////////////////
}

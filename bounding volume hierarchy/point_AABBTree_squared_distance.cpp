#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  //first create the priority queue that holds distance, object pointer pairs
  std::priority_queue< std::pair<double, std::shared_ptr<Object> >
                      ,std::vector<std::pair<double, std::shared_ptr<Object> > >, 
                      std::greater<std::pair<double, std::shared_ptr<Object> > > > 
                      wavefront; 
  
  //insert in the root to start
  double root_distance = point_box_squared_distance(query, root->box);
  wavefront.push(std::pair<double, std::shared_ptr<Object> >(root_distance, root));

  std::pair<double, std::shared_ptr<Object> > min_pair;
  double min_distance;
  std::shared_ptr<AABBTree> min_ptr;

  //now starts DFS
  double TEMP_MIN = std::numeric_limits<double>::infinity(); //to record current min distance
  bool hit = false; //to record if hits
  while(!wavefront.empty()){
    //get the front of the priority queue which has the shortest distance
    min_pair = wavefront.top();
    wavefront.pop();
    min_distance = min_pair.first;
    min_ptr = std::dynamic_pointer_cast<AABBTree> (min_pair.second);

    if(min_distance < TEMP_MIN){
      //shorter than min distance, so work on this pair
      if(min_ptr){
        //internal nodes
        if(min_ptr->left){
          //if has left child, add in the left child
          double left_distance = point_box_squared_distance(query, min_ptr->left->box);
          wavefront.push(std::pair<double, std::shared_ptr<Object> >(left_distance, min_ptr->left));
        }
        if(min_ptr->right){
          //if has right child, add in the right child
          double right_distance = point_box_squared_distance(query, min_ptr->right->box);
          wavefront.push(std::pair<double, std::shared_ptr<Object> >(right_distance, min_ptr->right));
        }
      }else{
        //leaf nodes, this is the actual objects that's closer, so update sqrd, hit and pointer 
        hit = true;
        TEMP_MIN = min_distance;
        descendant = min_pair.second;
      }
    }
  }

  sqrd = TEMP_MIN;
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

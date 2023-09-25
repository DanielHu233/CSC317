#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  //first create a queue(list) that holds the pair of nodes in A, B we encountered
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > wavefront;

  //first add in roots
  if(box_box_intersect(rootA->box, rootB->box)){
    wavefront.emplace_back(rootA, rootB);
  }

  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > current;
  //now starts searching through the trees using the queue
  while(!wavefront.empty()){
    //get the front of the queue
    std::shared_ptr<AABBTree> A_node, B_node;
    current = wavefront.front();
    A_node = std::dynamic_pointer_cast<AABBTree> (current.first);
    B_node = std::dynamic_pointer_cast<AABBTree> (current.second);
    wavefront.pop_front();
    
    //both are leaf nodes, actual intersecting pairs
    if(!A_node && !B_node){
      leaf_pairs.emplace_back(current);
    }else if(!A_node){
      //only A_node is leaf node
      if(B_node->left && box_box_intersect(current.first->box, B_node->left->box)){
        wavefront.emplace_back(current.first, B_node->left);
      }
      if(B_node->right && box_box_intersect(current.first->box, B_node->right->box)){
        wavefront.emplace_back(current.first, B_node->right);
      }
    }else if(!B_node){
      //only B_node is leaf node
      if(A_node->left && box_box_intersect(A_node->left->box, current.second->box)){
        wavefront.emplace_back(A_node->left, current.second);
      }
      if(A_node->right && box_box_intersect(A_node->right->box, current.second->box)){
        wavefront.emplace_back(A_node->right, current.second);
      }
    }else{
      //both are internal nodes
      if(A_node->left && B_node->left && box_box_intersect(A_node->left->box, B_node->left->box)){
        wavefront.emplace_back(A_node->left, B_node->left);
      }
      if(A_node->left && B_node->right && box_box_intersect(A_node->left->box, B_node->right->box)){
        wavefront.emplace_back(A_node->left, B_node->right);
      }
      if(A_node->right && B_node->left && box_box_intersect(A_node->right->box, B_node->left->box)){
        wavefront.emplace_back(A_node->right, B_node->left);
      }
      if(A_node->right && B_node->right && box_box_intersect(A_node->right->box, B_node->right->box)){
        wavefront.emplace_back(A_node->right, B_node->right);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

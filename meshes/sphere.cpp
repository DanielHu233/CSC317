#include "sphere.h"
#include <iostream>
#include "cmath"

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  //first calculate number of vertices and faces
  int face_num = num_faces_u * num_faces_v;
  int vertex_num = (num_faces_v + 1) * (num_faces_u + 1);

  //now fill in values
  V.resize(vertex_num, 3);
  F.resize(face_num,4);
  UV.resize(vertex_num,2);
  UF.resize(face_num,4);
  NV.resize(vertex_num,3);
  NF.resize(face_num,4);

  //computing normal vectors and 2d texture info
  int index = 0;
  double delta_v = M_PI * 2 / num_faces_u;
  double delta_u = M_PI / num_faces_v;
  //starts from the north pole and goes counter clockwise 
  //goes in the vertical(latitudinal) direction
  for(double i = 0;i <= num_faces_v;i++){
    //goes into horizontal(longitudinal) direction
    for(double j = 0;j <= num_faces_u;j++){
      //first compute the vertices positions
      //xyz coodinate
      V(index, 0) = sin(i*delta_u) * cos(j*delta_v);//x
      V(index, 1) = sin(i*delta_u) * sin(j*delta_v);//y
      V(index, 2) = cos(i*delta_u);//z            
      //compute normal vectors at vertices,it's same with v for sphere at the origin
      NV(index, 0) = sin(i*delta_u) * cos(j*delta_v);
      NV(index, 1) = sin(i*delta_u) * sin(j*delta_v);
      NV(index, 2) = cos(i*delta_u); 
      //compute corners
      UV(index, 0) = j/num_faces_u;//x coordinate is just j divided by num of js
      UV(index, 1) = i/num_faces_v;
      index++;
    }
  }

  index = 0;
  //now use the things computed above
  for(int i=1;i <= num_faces_v;i++){
    for(int j=1;j <= num_faces_u;j++){
      //compute vertices indexes
      int vertex_upleft = (i-1)*(num_faces_u+1)+j; //notice to start at 1
      int vertex_upright = vertex_upleft+1; //next point in the horizontal direction
      int vertex_downright = i*(num_faces_u+1)+j+1; //next point in the vertical direction than vertex_upright
      int vertex_downleft = vertex_downright-1; //to the left of downright
      //all teh following uses same index conventions
      F.row(index) = Eigen::RowVector4i(vertex_upleft, vertex_upright, vertex_downright, vertex_downleft);
      NF.row(index) = Eigen::RowVector4i(vertex_upleft, vertex_upright, vertex_downright, vertex_downleft);
      UF.row(index) = Eigen::RowVector4i(vertex_upleft, vertex_upright, vertex_downright, vertex_downleft); 
      index++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

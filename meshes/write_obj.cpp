#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

using namespace std;
bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  //open file
  fstream writer;
  writer.open(filename);
  if(!writer.is_open()){
    return false;
  }
  //consulted https://en.wikipedia.org/wiki/Wavefront_.obj_file
  //write vertex V
  writer<<"# List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.0."<<endl;
  for(int i = 0;i < V.rows();i++){
    writer<<"v "<<V(i, 0)<<" "<<V(i, 1)<<" "<<V(i, 2)<<endl;
  }
  //write UV positions
  writer<<"# List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0."<<endl;
  for(int i = 0;i < UV.rows();i++){
    writer<<"vt "<<UV(i, 0)<<" "<<UV(i, 1)<<endl;
  }
  //write normal vectors
  writer<<"# List of vertex normals in (x,y,z) form; normals might not be unit vectors."<<endl;
  for(int i = 0;i < NV.rows();i++){
    writer<<"vn "<<NV(i, 0)<<" "<<NV(i, 1)<<" "<<NV(i, 2)<<endl;
  }
  //write face indices
  writer<<"# Polygonal face element (see below)"<<endl;
  for(int i = 0;i < F.rows();i++){
    writer<<"f ";
    for(int j = 0;j < F.cols();j++){
      writer<<F(i, j)<<"/"<<UF(i, j)<<"/"<<NF(i, j)<<" ";
    }
    writer<<endl;
  }
  writer.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

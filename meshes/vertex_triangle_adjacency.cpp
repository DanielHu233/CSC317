#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  //loop through all faces
  for(int i = 0;i < F.rows();i++){
    for(int j = 0;j < F.cols();j++){
      //look for adjacent using face vertices
      VF[F(i, j)].push_back(i);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


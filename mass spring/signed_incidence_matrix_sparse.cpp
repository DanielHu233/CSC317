#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;
  A.resize(E.rows(),n);

  //for the e-th row of corresponding to edge connecting vertices and we'll assign values: k == i, Aek + 1, k == j, Aek - 1
  for(int e = 0;e < E.rows();e++){
    //e-th row
    for(int k = 0;k < n;k++){
      if(k == E(e, 0)){
        ijv.emplace_back(e, k, 1);
      }else if(k == E(e, 1)){
        ijv.emplace_back(e, k, -1);
      }
    }
  }

  A.setFromTriplets(ijv.begin(),ijv.end());
  //////////////////////////////////////////////////////////////////////////////
}

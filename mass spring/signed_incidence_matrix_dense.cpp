#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  A = Eigen::MatrixXd::Zero(E.rows(),n);
  //for the e-th row of corresponding to edge connecting vertices and we'll assign values: k == i, Aek + 1, k == j, Aek - 1
  for(int e = 0;e < E.rows();e++){
    //e-th row
    for(int k = 0;k < n;k++){
      if(k == E(e, 0)){
        A(e, k)++;
      }else if(k == E(e, 1)){
        A(e, k)--;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////
}

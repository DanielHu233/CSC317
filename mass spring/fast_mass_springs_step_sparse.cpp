#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd P = Ucur;
  for(int iter = 0;iter < 1;iter++)
  {
    Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(),3);
    for(int i = 0;i < r.size();i++){
      d.row(i) = r[i] * (P.row(E(i, 0)) - P.row(E(i, 1))).normalized();
    }
    
    Eigen::MatrixXd y = 1 / pow(delta_t, 2) * M * (2 * Ucur - Uprev) + fext;
    long int w = 1e10; 
    Eigen::MatrixXd b = k * A.transpose() * d + y + w * C.transpose() * C * V;

    Unext = prefactorization.solve(b);
  }
  //////////////////////////////////////////////////////////////////////////////
}

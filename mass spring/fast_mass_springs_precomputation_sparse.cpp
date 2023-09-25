#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  const int n = V.rows();
  Eigen::SparseMatrix<double> Q(n,n);
  
  //edge lengths
  r.resize(E.rows());
  for(int i = 0;i < E.rows();i++){
    Eigen::VectorXd Edge = V.row(E(i, 0)) - V.row(E(i, 1));
    r[i] = Edge.norm();
  }

  //mass matrix(diagonal)
  std::vector<Eigen::Triplet<double> > ijv_M;
  M.resize(V.rows(), V.rows());
  for(int i = 0;i < V.rows();i++){
    //M(i, i) = m[i];
    ijv_M.emplace_back(i, i, m[i]);
  }
  M.setFromTriplets(ijv_M.begin(), ijv_M.end());

  //signed indices matrix_dense
  signed_incidence_matrix_sparse(V.rows(), E, A);

  //selection matrix
  std::vector<Eigen::Triplet<double> > ijv_C;
  C.resize(b.size(), V.rows());
  for(int i = 0;i < b.size();i++){
    //C(i, b[i]) = 1;
    ijv_C.emplace_back(i, b[i], 1);
  }
  C.setFromTriplets(ijv_C.begin(), ijv_C.end());

  //Q = kA^TA + 1/delta_t^2 * M + extra term
  long int w = 1e10;
  Q = k * A.transpose() * A + 1 / pow(delta_t, 2) * M + w * C.transpose() * C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}

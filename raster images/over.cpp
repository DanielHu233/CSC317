#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////

  //The alpha over formula is from https://en.wikipedia.org/wiki/Alpha_compositing 
  for(int i = 0;i < width*height;i++){
    double alphaA = A[i*4 + 3]/255.0;
    double alphaB = B[i*4 + 3]/255.0;
    double alpha = alphaA + alphaB * (1 - alphaA);

    double C_A_r = A[i*4];
    double C_B_r = B[i*4];
    double C_A_g = A[i*4 + 1];
    double C_B_g = B[i*4 + 1];
    double C_A_b = A[i*4 + 2];
    double C_B_b = B[i*4 + 2];
    double C_r = (C_A_r*alphaA + C_B_r*alphaB*(1-alphaA)) / alpha;
    double C_g = (C_A_g*alphaA + C_B_g*alphaB*(1-alphaA)) / alpha;
    double C_b = (C_A_b*alphaA + C_B_b*alphaB*(1-alphaA)) / alpha;

    C[i*4] = C_r;
    C[i*4 + 1] = C_g;
    C[i*4 + 2] = C_b;
    C[i*4 + 3] = alpha * 255.0;
  }
  ////////////////////////////////////////////////////////////////////////////
}

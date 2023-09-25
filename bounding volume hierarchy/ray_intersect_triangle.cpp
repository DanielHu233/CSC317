#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  double a, b, c, d, e, f, g, h, i, j, k, l, xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
  double beta, gama, M;

  Eigen::Vector3d A_ = (Eigen::Vector3d) A;
  Eigen::Vector3d B_ = (Eigen::Vector3d) B;
  Eigen::Vector3d C_ = (Eigen::Vector3d) C;

  xa=A_[0];xb=B_[0];xc=C_[0];
  xd=ray.direction[0];
  xe=ray.origin[0];
  ya=A_[1];yb=B_[1];yc=C_[1];
  yd=ray.direction[1];
  ye=ray.origin[1];
  za=A_[2];zb=B_[2];zc=C_[2];
  zd=ray.direction[2];
  ze=ray.origin[2];

  //compute the 3*3 matrix components, using formulae from book p78
  a=xa-xb;
  b=ya-yb;
  c=za-zb;
  d=xa-xc;
  e=ya-yc;
  f=za-zc;
  g=xd;
  h=yd;
  i=zd;
  
  j=xa-xe; 
  k=ya-ye; 
  l=za-ze;
  
  M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
  beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
  gama = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
  double T = -(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;

  if(T >= min_t && T <= max_t && gama >= 0 && beta >= 0 && (beta+gama) <= 1){
    t = T;
    return true;
  }else{  
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}


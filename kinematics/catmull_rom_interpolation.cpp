#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  //consulted https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  if(keyframes.size() == 0){
  	return Eigen::Vector3d(0, 0, 0);
  }
  //calculate which frame we want
  t = std::fmod(t, keyframes.back().first);
  int i = 0;
  while(i < keyframes.size()){
    if(keyframes[i].first < t){
      i++;
    }else{
      break;
    }
  }

  Eigen::Vector3d P0, P1, P2, P3; //points
  double t0, t1, t2, t3; //times
  if(i < 2 || i == keyframes.size() - 1){
    //corner cases
    P0 = keyframes[i-1].second;
    t0 = keyframes[i-1].first;
    P1 = keyframes[i].second;
    t1 = keyframes[i].first;
    return ((t1 - t) / (t1 - t0)) * P0 + ((t - t0) / (t1 - t0)) * P1;
  }else{
    P0 = keyframes[i - 2].second;
    t0 = keyframes[i - 2].first;
    P1 = keyframes[i - 1].second;
    t1 = keyframes[i - 1].first;
    P2 = keyframes[i].second;
    t2 = keyframes[i].first;
    P3 = keyframes[i + 1].second;
    t3 = keyframes[i + 1].first;

    Eigen::Vector3d A1, A2, A3, B1, B2, C;
    A1 = ((t1 - t) / (t1 - t0)) * P0 + ((t - t0) / (t1 - t0)) * P1;
  	A2 = ((t2 - t) / (t2 - t1)) * P1 + ((t - t1) / (t2 - t1)) * P2;
  	A3 = ((t3 - t) / (t3 - t2)) * P2 + ((t - t2) / (t3 - t2)) * P3;

  	B1 = ((t2 - t) / (t2 - t0)) * A1 + ((t - t0) / (t2 - t0)) * A2;
  	B2 = ((t3 - t) / (t3 - t1)) * A2 + ((t - t1) / (t3 - t1)) * A3;

  	C = ((t2 - t) / (t2 - t1)) * B1 + ((t - t1) / (t2 - t1)) * B2;
    return C;
  }
  /////////////////////////////////////////////////////////////////////////////
}

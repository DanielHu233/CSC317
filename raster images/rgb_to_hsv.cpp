#include "rgb_to_hsv.h"
#include "math.h"

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////

  //formula for hsv transformation is from https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
  double R = r;
  double G = g;
  double B = b;
  //compute cmax, cmin
  double cmax = fmax(R, fmax(G, B));
  double cmin = fmin(R, fmin(G, B));
  double difference = cmax - cmin;
  
  if(cmax == cmin){
    h = 0;
  }
  //compute h
  // if cmax equal r then compute h
  else if (cmax == R)
      h = fmod((60.0 * ((G - B) / difference) + 360.0), 360.0);

  // if cmax equal g then compute h
  else if (cmax == G)
      h = fmod((60.0 * ((B - R) / difference) + 120.0), 360.0);

  // if cmax equal b then compute h
  else if (cmax == B)
      h = fmod((60.0 * ((R - G) / difference) + 240.0), 360.0);

  //compute s
  // if cmax equal zero
  if (cmax == 0)
      s = 0;
  else
      s = difference / cmax;

  //compute v
  v = cmax;
  ////////////////////////////////////////////////////////////////////////////
}

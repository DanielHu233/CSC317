#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < width*height;i++){
    double R = rgb[i*3] / 255.0;
    double G = rgb[i*3 + 1] / 255.0;
    double B = rgb[i*3 + 2] / 255.0;
    double h, s, v;

    rgb_to_hsv(R, G, B, h, s, v);
    h = fmod(h + shift, 360.0);
    hsv_to_rgb(h, s, v, R, G, B);

    shifted[i*3] = R * 255.0;
    shifted[i*3 + 1] = G * 255.0;
    shifted[i*3 + 2] = B * 255.0;
  }
  ////////////////////////////////////////////////////////////////////////////
}

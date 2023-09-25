#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < width*height;i++){
    double R = rgb[i*3] / 255.0;
    double G = rgb[i*3 + 1] / 255.0;
    double B = rgb[i*3 + 2] / 255.0;
    double h, s, v;

    rgb_to_hsv(R, G, B, h, s, v);
    s = s * (1 - factor);
    hsv_to_rgb(h, s, v, R, G, B);

    desaturated[i*3] = R * 255.0;
    desaturated[i*3 + 1] = G * 255.0;
    desaturated[i*3 + 2] = B * 255.0;
  }
  ////////////////////////////////////////////////////////////////////////////
}

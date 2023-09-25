#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < gray.size();i++){
    gray[i] = rgb[i*3] * 0.2126 + rgb[i*3+1] * 0.7152 + rgb[i*3+2] * 0.0722;
  }
  ////////////////////////////////////////////////////////////////////////////
}



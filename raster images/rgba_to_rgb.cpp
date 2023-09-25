#include "rgba_to_rgb.h"
#include <iostream>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  //std::cout<<rgba.size()<<std::endl;
  long long int countR = 0;
  for(long long int i = 0;i < rgba.size();i++){
    if(i % 4 != 3){
      rgb[countR] = rgba[i];
      countR++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
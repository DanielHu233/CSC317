#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < height;i++){
    for(int j = 0;j < width;j++){
      if((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1)){
        //green
        bayer[i*width + j] = rgb[i*width*3 + j*3 + 1];
      }else if(i%2 == 1 && j%2 == 0){
        //red
        bayer[i*width + j] = rgb[i*width*3 + j*3];
      }else{
        //blue
        bayer[i*width + j] = rgb[i*width*3 + j*3 + 2];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

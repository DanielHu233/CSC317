#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < height;i++){
    for(int j = 0;j < width;j++){
      reflected[i*width*num_channels + j*num_channels] = input[i*width*num_channels + (width - j -1)*num_channels];
      reflected[i*width*num_channels + j*num_channels + 1] = input[i*width*num_channels + (width - j -1)*num_channels + 1];
      reflected[i*width*num_channels + j*num_channels + 2] = input[i*width*num_channels + (width - j -1)*num_channels + 2];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

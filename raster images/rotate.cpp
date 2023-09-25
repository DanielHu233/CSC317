#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < width;i++){
    for(int j = 0;j < height;j++){
      rotated[i*height*num_channels + j*num_channels] = input[j*width*num_channels + (width - i - 1)*num_channels];
      rotated[i*height*num_channels + j*num_channels + 1] = input[j*width*num_channels + (width - i - 1)*num_channels + 1];
      rotated[i*height*num_channels + j*num_channels + 2] = input[j*width*num_channels + (width - i - 1)*num_channels + 2];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

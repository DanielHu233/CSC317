#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0;i < height;i++){
    for(int j = 0;j < width;j++){
      if((i%2 == 0 && j%2 == 0)){
        //on green block
        //first determine red value
        int red = 0;
        int count = 0;
        if(i - 1 >= 0){
          red += bayer[(i-1)*width + j];
          count++;
        }
        if(i + 1 < height){
          red += bayer[(i+1)*width + j];
          count++;
        }
        red = red/count;
        rgb[i*width*3 + j*3] = red;
        //determine blue value
        int blue = 0;
        count = 0;
        if(j - 1 >= 0){
          blue += bayer[i*width + j-1];
          count++;
        }
        if(j + 1 < width){
          blue += bayer[i*width + j+1];
          count++;
        }
        blue = blue/count;
        rgb[i*width*3 + j*3 + 2] = blue;
        //fill in green
        rgb[i*width*3 + j*3 + 1] = bayer[i*width + j];
      }else if(i%2 == 1 && j%2 == 1){
        //on another type if green block
        //first determine blue value
        int blue = 0;
        int count = 0;
        if(i - 1 >= 0){
          blue += bayer[(i-1)*width + j];
          count++;
        }
        if(i + 1 < height){
          blue += bayer[(i+1)*width + j];
          count++;
        }
        blue = blue/count;
        rgb[i*width*3 + j*3 +2] = blue;
        //determine red value
        int red = 0;
        count = 0;
        if(j - 1 >= 0){
          red += bayer[i*width + j-1];
          count++;
        }
        if(j + 1 < width){
          red += bayer[i*width + j+1];
          count++;
        }
        red = red/count;
        rgb[i*width*3 + j*3] = red;
        //fill in green
        rgb[i*width*3 + j*3 + 1] = bayer[i*width + j];
      }else if(i%2 == 0 && j%2 == 1){
        //on blue blocks
        //first determine green value
        int green = 0;
        int count = 0;
        if(i - 1 >= 0){
          green += bayer[(i-1)*width + j];
          count++;
        }
        if(i + 1 < height){
          green += bayer[(i+1)*width + j];
          count++;
        }
        if(j - 1 >= 0){
          green += bayer[i*width + j-1];
          count++;
        }
        if(j + 1 < width){
          green += bayer[i*width + j+1];
          count++;
        }
        green = green/count;
        rgb[i*width*3 + j*3 + 1] = green;
        //determine red
        int red = 0;
        count = 0;
        if(i - 1 >= 0 && j - 1 >= 0){
          red += bayer[(i-1)*width + j-1];
          count++;
        }
        if(i - 1 >= 0 && j + 1 < width){
          red += bayer[(i-1)*width + j+1];
          count++;
        }
        if(i + 1 < height && j - 1 >= 0){
          red += bayer[(i+1)*width + j-1];
          count++;
        }
        if(i + 1 < height && j + 1 < width){
          red += bayer[(i+1)*width + j+1];
          count++;
        }
        red = red/count;
        rgb[i*width*3 + j*3] = red;
        //fill in blue
        rgb[i*width*3 + j*3 + 2] = bayer[i*width + j];
      }else{
        //on red blocks
        //first determine green value
        int green = 0;
        int count = 0;
        if(i - 1 >= 0){
          green += bayer[(i-1)*width + j];
          count++;
        }
        if(i + 1 < height){
          green += bayer[(i+1)*width + j];
          count++;
        }
        if(j - 1 >= 0){
          green += bayer[i*width + j-1];
          count++;
        }
        if(j + 1 < width){
          green += bayer[i*width + j+1];
          count++;
        }
        green = green/count;
        rgb[i*width*3 + j*3 + 1] = green;
        //determine blue
        int blue = 0;
        count = 0;
        if(i - 1 >= 0 && j - 1 >= 0){
          blue += bayer[(i-1)*width + j-1];
          count++;
        }
        if(i - 1 >= 0 && j + 1 < width){
          blue += bayer[(i-1)*width + j+1];
          count++;
        }
        if(i + 1 < height && j - 1 >= 0){
          blue += bayer[(i+1)*width + j-1];
          count++;
        }
        if(i + 1 < height && j + 1 < width){
          blue += bayer[(i+1)*width + j+1];
          count++;
        }
        blue = blue/count;
        rgb[i*width*3 + j*3 + 2] = blue;
        //fill in red
        rgb[i*width*3 + j*3] = bayer[i*width + j];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

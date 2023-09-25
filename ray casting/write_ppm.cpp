#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

using namespace std;

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////  
  if(num_channels == 3){
    //RGB 
    ofstream writer(filename);
    //file title
    writer<<"P3"<<endl<<width<<" "<<height<<endl<<255<<endl;
    //write in rgb data
    for(int i = 0;i < data.size();i++){
      writer<<int(data[i])<<" ";
    }

    writer.close();
    return true;
  }else{
    //grey scale
    ofstream writer(filename);
    writer<<"P2"<<endl<<width<<" "<<height<<endl<<255<<endl;
    for(int i = 0;i < data.size();i++){
      writer<<int(data[i])<<" ";
    }

    writer.close();
    return true;
  }
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

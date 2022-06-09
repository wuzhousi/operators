#ifndef CONVERT_DATA_STRUCTURE
#define CONVERT_DATA_STRUCTURE

#include "mini_mat.h"

template<typename T>
void FromCVRGBOrBGR(unsigned char* rgb, MiniMat& m, T data_type){

  int w = m.w;
  int h = m.h;

  T* ptr0 = (T*) m.Channel(0);
  T* ptr1 = (T*) m.Channel(1);
  T* ptr2 = (T*) m.Channel(2); 

  for (int y = 0; y < h; y++)
  {
    for (int x=0; x < w; x++)
    {
      *ptr0 = rgb[0];
      *ptr1 = rgb[1];
      *ptr2 = rgb[2];

      rgb += 3;
      ptr0++;
      ptr1++;
      ptr2++;
    }
  }
}

template<typename T>
void ToCVRGBOrBGR(unsigned char* rgb, MiniMat& m, T data_type){
  int w = m.w;
  int h = m.h;

  T* ptr0 = (T*) m.Channel(0);
  T* ptr1 = (T*) m.Channel(1);
  T* ptr2 = (T*) m.Channel(2);

  for (int y = 0; y < h; y++)
  {
    for (int x=0; x < w; x++)
    {
      
      rgb[0] = (unsigned char) *ptr0;
      rgb[1] = (unsigned char) *ptr1;
      rgb[2] = (unsigned char) *ptr2;

      rgb += 3;
      ptr0++;
      ptr1++;
      ptr2++;
    }
  }  
}

#endif
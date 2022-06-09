#include "mini_mat.h"

#include "allocator.h"

void MiniMat::Create(int w, int elemsize){
  int sz = AlignSize(w * elemsize, 16);
  cstep = w;
  data = FastMalloc(sz);
}

void MiniMat::Create(int w, int h, int elemsize){
  int sz = AlignSize(w * h * elemsize, 16);
  cstep = w * h;
  data = FastMalloc(sz);
}

void MiniMat::Create(int w, int h, int c, int elemsize){
  int sz = AlignSize(w * h * elemsize, 16);
  cstep = sz / elemsize;
  data = FastMalloc(sz * c);
}

void* MiniMat::Channel(int i){
  return (void*) (((unsigned char*) data) + i * cstep * elemsize);
}

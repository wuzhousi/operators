#ifndef VISION_PRE_POST_OPS
#define VISION_PRE_POST_OPS

#include <iostream>

#include "omp.h"

void FlipVert(void* src,int src_w,  int src_h, int src_c, int src_elemsize, int src_cstep, void* dst);

void FlipHoriz(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst);

void Crop(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst, int x, int y, int dst_w, int dst_h, int dst_cstep);

void Pad(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst, int pad_t, int pad_b, int pad_r, int pad_l, int dst_w, int dst_h, int dst_cstep);

#endif
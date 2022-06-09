#include "vision_pre_post_ops.h"

void FlipVert(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst){
  int h_loop_times = src_h / 2;
  int w_loop_times = (src_w * src_elemsize) / 32; 
  int w_remains = (src_w * src_elemsize) % 32; 

  for(int c=0; c<src_c; c++){
    register unsigned char * s = ((unsigned char *) src)+c*src_cstep*src_elemsize;
    register unsigned char * d = ((unsigned char *) dst)+c*src_cstep*src_elemsize;
    
    omp_set_num_threads(4);
    #pragma omp parallel for
    for(int i=0; i<h_loop_times; i++){
      register double* tptr = (double*) (s+src_w*i*src_elemsize);
      register double* bptr = (double*) (s+src_w*(src_h-1-i)*src_elemsize);
      register double* ntptr = (double*) (d+src_w*i*src_elemsize);
      register double* nbptr = (double*) (d+src_w*(src_h-1-i)*src_elemsize);

      for(int j=0; j<w_loop_times; j++){

        *nbptr = *tptr;
        *ntptr = *bptr;

        *(nbptr+1) = *(tptr+1);
        *(ntptr+1) = *(bptr+1);

        *(nbptr+2) = *(tptr+2);
        *(ntptr+2) = *(bptr+2);

        *(nbptr+3) = *(tptr+3);
        *(ntptr+3) = *(bptr+3);

        tptr+=4;
        bptr+=4;
        ntptr+=4;
        nbptr+=4;           
      }

      unsigned char* uctptr = (unsigned char*) tptr;
      unsigned char* ucbptr = (unsigned char*) bptr;
      unsigned char* ucntptr = (unsigned char*) ntptr;
      unsigned char* ucnbptr = (unsigned char*) nbptr;
      for(int j=0; j<w_remains; j++){
        *ucnbptr = *uctptr;
        *ucntptr = *ucbptr;

        uctptr++;
        ucbptr++;
        ucntptr++;
        ucnbptr++;
      }
    }
  }
}

void FlipHoriz(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst){
  int h_loop_times = src_h / 1;
  int w_loop_times = (src_w * src_elemsize) / 4; 
  int w_remains = (src_w * src_elemsize) % 4; 

  for(int c=0; c<src_c; c++){
    register unsigned char * s = ((unsigned char *) src)+c*src_cstep*src_elemsize;
    register unsigned char * d = ((unsigned char *) dst)+c*src_cstep*src_elemsize;
    
    omp_set_num_threads(4);
    #pragma omp parallel for
    for(int i=0; i<h_loop_times; i++){
      int lptr_addr = src_w*i*1*src_elemsize;
      int nrptr_addr = src_w*i*1*src_elemsize+(src_w-1);

      register unsigned char* lptr = s+lptr_addr;
      register unsigned char* nrptr = d+nrptr_addr;

      for(int j=0; j<w_loop_times; j++){
        *nrptr = *lptr;
        *(nrptr-1) = *(lptr+1);
        *(nrptr-2) = *(lptr+2);
        *(nrptr-3) = *(lptr+3);
        nrptr-=4;
        lptr+=4;
      }

      for(int i=0; i<w_remains; i++){
        *nrptr = *lptr;

        nrptr-=1;
        lptr+=1;
      }
    }
  }
}

void Crop(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst, int x, int y, int dst_w, int dst_h, int dst_cstep){
  int w_loop_times = (dst_w * src_elemsize) / 32; 
  int w_remains = (dst_w * src_elemsize) % 32; 

  for(int c=0; c<src_c; c++){
    register unsigned char * s = ((unsigned char *) src)+c*src_cstep*src_elemsize;
    register unsigned char * d = ((unsigned char *) dst)+c*dst_cstep*src_elemsize;

    omp_set_num_threads(4);
    #pragma omp parallel for
    for(int i=0; i<dst_h; i++){
      register double* ptr = (double*) (s+(src_w*(i+y)+x)*src_elemsize);
      register double* nptr = (double*) (d+dst_w*i*src_elemsize);

      for(int j=0; j<w_loop_times; j++){
        *nptr = *ptr;
        *(nptr+1) = *(ptr+1);
        *(nptr+2) = *(ptr+2);
        *(nptr+3) = *(ptr+3);

        nptr+=4;
        ptr+=4;          
      }

      unsigned char* ucptr = (unsigned char*) ptr;
      unsigned char* ucnptr = (unsigned char*) nptr;
      for(int j=0; j<w_remains; j++){
        *ucnptr = *ucptr;
        ucptr++;
        ucnptr++;
      }
    }
  }
}

void Pad(void* src, int src_w, int src_h, int src_c, int src_elemsize, int src_cstep, void* dst, int pad_top, int pad_bottom, int pad_left, int pad_right, int dst_w, int dst_h, int dst_cstep){
  int w_loop_times = (src_w * src_elemsize) / 32; 
  int w_remains = (src_w * src_elemsize) % 32; 

  for(int c=0; c<src_c; c++){
    register unsigned char * s = ((unsigned char *) src)+c*src_cstep*src_elemsize;
    register unsigned char * d = ((unsigned char *) dst)+c*dst_cstep*src_elemsize;

    omp_set_num_threads(4);
    #pragma omp parallel for
    for(int i=0; i<src_h; i++){
      register double* ptr = (double*) (s+src_w*i*src_elemsize);
      register double* nptr = (double*) (d+(dst_w*(i+pad_top)+pad_left)*src_elemsize);

      for(int j=0; j<w_loop_times; j++){
        *nptr = *ptr;
        *(nptr+1) = *(ptr+1);
        *(nptr+2) = *(ptr+2);
        *(nptr+3) = *(ptr+3);

        nptr+=4;
        ptr+=4;          
      }

      unsigned char* ucptr = (unsigned char*) ptr;
      unsigned char* ucnptr = (unsigned char*) nptr;
      for(int j=0; j<w_remains; j++){
        *ucnptr = *ucptr;
        ucptr++;
        ucnptr++;
      }
    }
  }
}



// void Pad(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int top_pad, int bottom_pad, int left_pad, int right_pad){
//   int channels = ptr->get_channels();
//   int cols = ptr->get_cols();
//   int rows = ptr->get_rows();
//   unsigned unsigned char* array_ptr = ptr->get_array_ptr();

//   int new_rows = top_pad + bottom_pad + rows;
//   int new_cols = left_pad + right_pad + cols;

//   unsigned unsigned char* new_array_ptr = static_cast<unsigned unsigned char*>(malloc(channels * new_rows * new_cols * sizeof(unsigned unsigned char)));

//   for(int k=0; k<channels; k++){
//     int size = k * rows * cols;
//     int nsize = k * new_rows * new_cols;

//     register unsigned unsigned char *np, *p;

//     for(int j=0; j<cols; j++){
//       p = array_ptr + size + j * rows;
//       np = new_array_ptr + nsize + (j+left_pad) * new_rows + top_pad;
//       for(int i=0; i<rows; i+=32){
//         // new_array_ptr[k * new_rows * new_cols + (j+left_pad) * new_rows + (i+top_pad)] = array_ptr[k * rows * cols + j * rows + i];
//         *((double*)np) = *((double*)p);
//         *((double*)np+1) = *((double*)p+1);
//         *((double*)np+2) = *((double*)p+2);
//         *((double*)np+3) = *((double*)p+3);

//         np+=32;
//         p+=32;
//       }
//     }
//   }

//   out_ptr->Reset(channels, new_rows, new_cols, new_array_ptr);
// }

// void Erase(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width, unsigned unsigned char value){
//   int channels = ptr->get_channels();
//   int cols = ptr->get_cols();
//   int rows = ptr->get_rows();
//   unsigned unsigned char* array_ptr = ptr->get_array_ptr();

//   if(x<0 || y<0){
//     return;
//   }

//   unsigned unsigned char* new_array_ptr = static_cast<unsigned unsigned char*>(malloc(channels * rows * cols * sizeof(unsigned unsigned char)));
//   memcpy(new_array_ptr, array_ptr, channels * rows * cols * sizeof(unsigned unsigned char));

//   int min_h = std::min(x+height, rows);
//   int min_w = std::min(y+width, cols);

//   for(int k=0; k<channels; k++){
//     for(int j=y; j<min_w; j++){
//       for(int i=x; i<min_h; i++){
//         new_array_ptr[k * rows * cols + j * rows + i] = value;
//       }
//     }
//   }

//   out_ptr->Reset(channels, rows, cols, new_array_ptr);
// }

// void ConvertBGRToGray(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr){
//   int cols = ptr->get_cols();
//   int rows = ptr->get_rows();
//   unsigned unsigned char* array_ptr = ptr->get_array_ptr();  

//   unsigned unsigned char* new_array_ptr = static_cast<unsigned unsigned char*>(malloc(rows * cols * sizeof(unsigned unsigned char)));
//   memset(new_array_ptr, static_cast<int64_t>(0), rows * cols * sizeof(unsigned unsigned char));


//   register unsigned unsigned char *np, *p1, *p2, *p3;
//   np = new_array_ptr;
//   p1 = array_ptr;
//   p2 = array_ptr + rows * cols;
//   p3 = array_ptr + 2 * rows * cols;

//   // float r[] = {0.0f, 0.0f, 0.0f, 0.0f};
//   // float g[] = {0.0f, 0.0f, 0.0f, 0.0f};
//   // float b[] = {0.0f, 0.0f, 0.0f, 0.0f};

//   // float k1[] = {0.114f, 0.114f, 0.114f, 0.114f};
//   // float k2[] = {0.587f, 0.587f, 0.587f, 0.587f};
//   // float k3[] = {0.2989f, 0.2989f, 0.2989f, 0.2989f};

//   // __m128 mk1 = _mm_load_ps(&k1[0]);
//   // __m128 mk2 = _mm_load_ps(&k2[0]);
//   // __m128 mk3 = _mm_load_ps(&k3[0]);

//   // __m128 mr;
//   // __m128 mg;
//   // __m128 mb;
//   // __m128 res;
//   // for(int j=0; j<cols; j++){
//   //   for(int i=0; i<rows; i+=4){
//   //     r[0] = (float) *p1;
//   //     r[1] = (float) *(p1+1);
//   //     r[2] = (float) *(p1+2);
//   //     r[3] = (float) *(p1+3);

//   //     g[0] = (float) *p2;
//   //     g[1] = (float) *(p2+1);
//   //     g[2] = (float) *(p2+2);
//   //     g[3] = (float) *(p2+3);

//   //     b[0] = (float) *p3;
//   //     b[1] = (float) *(p3+1);
//   //     b[2] = (float) *(p3+2);
//   //     b[3] = (float) *(p3+3);

//   //     mr = _mm_load_ps(&r[0]);
//   //     mg = _mm_load_ps(&g[0]);
//   //     mb = _mm_load_ps(&b[0]);

//   //     mr = _mm_mul_ps(mk1, mr);
//   //     mg = _mm_mul_ps(mk2, mg);
//   //     mb = _mm_mul_ps(mk3, mb);

//   //     res = _mm_add_ps(mr, mg);
//   //     res = _mm_add_ps(mb, res);

//   //     *np = (unsigned unsigned char) res[0];
//   //     *(np+1) = (unsigned unsigned char) res[1];
//   //     *(np+2) = (unsigned unsigned char) res[2];
//   //     *(np+3) = (unsigned unsigned char) res[3];

//   //     np+=4;
//   //     p1+=4;
//   //     p2+=4;
//   //     p3+=4;
//   //   }
//   // }


//   for(int j=0; j<cols; j++){
//     for(int i=0; i<rows; i+=4){
//       // *np = (unsigned unsigned char) (0.114 * ((float)*p1) + 0.587 * ((float)*p2) + 0.587 * ((float)*p3));
//       // *(np+1) = (unsigned unsigned char) (0.114 * ((float)*(p1+1)) + 0.587 * ((float)*(p2+1)) + 0.587 * ((float)*(p3+1)));
//       // *(np+2) = (unsigned unsigned char) (0.114 * ((float)*(p1+2)) + 0.587 * ((float)*(p2+2)) + 0.587 * ((float)*(p3+2)));
//       // *(np+3) = (unsigned unsigned char) (0.114 * ((float)*(p1+3)) + 0.587 * ((float)*(p2+3)) + 0.587 * ((float)*(p3+3)));

//       *np = 0.114 * *p1 + 0.587 * *p2 + 0.2989 * *p3;
//       *(np+1) = 0.114 * *(p1+1) + 0.587 * *(p2+1) + 0.2989 * *(p3+1);
//       *(np+2) = 0.114 * *(p1+2) + 0.587 * *(p2+2) + 0.2989 * *(p3+2);
//       *(np+3) = 0.114 * *(p1+3) + 0.587 * *(p2+3) + 0.2989 * *(p3+3);

//       np+=4;
//       p1+=4;
//       p2+=4;
//       p3+=4;
//     }
//   }
//   out_ptr->Reset(1, rows, cols, new_array_ptr);
// }
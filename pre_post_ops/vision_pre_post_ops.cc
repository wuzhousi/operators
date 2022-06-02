#include "vision_pre_post_ops.h"

#include <xmmintrin.h>

// using namespace cv;

// void mflip(cv::InputArray _src, cv::OutputArray _dst, int flip_mode )
// {
//     CV_INSTRUMENT_REGION();

//     CV_Assert( _src.dims() <= 2 );
//     cv::Size size = _src.size();

//     if (flip_mode < 0)
//     {
//         if (size.width == 1)
//             flip_mode = 0;
//         if (size.height == 1)
//             flip_mode = 1;
//     }

//     if ((size.width == 1 && flip_mode > 0) ||
//         (size.height == 1 && flip_mode == 0) ||
//         (size.height == 1 && size.width == 1 && flip_mode < 0))
//     {
//         return _src.copyTo(_dst);
//     }

//     CV_OCL_RUN( _dst.isUMat(), ocl_flip(_src, _dst, flip_mode))

//     cv::Mat src = _src.getMat();
//     int type = src.type();
//     _dst.create( size, type );
//     cv::Mat dst = _dst.getMat();

//     CV_IPP_RUN_FAST(ipp_flip(src, dst, flip_mode));

//     size_t esz = CV_ELEM_SIZE(type);

//     if( flip_mode <= 0 )
//         flipVert( src.ptr(), src.step, dst.ptr(), dst.step, src.size(), esz );
//     else
//         flipHoriz( src.ptr(), src.step, dst.ptr(), dst.step, src.size(), esz );

//     if( flip_mode < 0 )
//         flipHoriz( dst.ptr(), dst.step, dst.ptr(), dst.step, dst.size(), esz );
// }

// void flipHoriz( const uchar* src, size_t sstep, uchar* dst, size_t dstep, cv::Size size, size_t esz)
// {
//     int i, j, limit = (int)(((size.width + 1)/2)*esz);
//     cv::AutoBuffer<int> _tab(size.width*esz);
//     int* tab = _tab.data();

//     for( i = 0; i < size.width; i++ )
//         for( size_t k = 0; k < esz; k++ )
//             tab[i*esz + k] = (int)((size.width - i - 1)*esz + k);

//     for( ; size.height--; src += sstep, dst += dstep )
//     {
//         for( i = 0; i < limit; i++ )
//         {
//             j = tab[i];
//             uchar t0 = src[i], t1 = src[j];
//             dst[i] = t1; dst[j] = t0;
//         }
//     }
// }

// void flipVert( const uchar* src0, size_t sstep, uchar* dst0, size_t dstep, cv::Size size, size_t esz)
// {
//     const uchar* src1 = src0 + (size.height - 1)*sstep;
//     uchar* dst1 = dst0 + (size.height - 1)*dstep;
//     size.width *= (int)esz;

//     for( int y = 0; y < (size.height + 1)/2; y++, src0 += sstep, src1 -= sstep,
//                                                   dst0 += dstep, dst1 -= dstep )
//     {
//         int i = 0;
//         if( ((size_t)src0|(size_t)dst0|(size_t)src1|(size_t)dst1) % sizeof(int) == 0 )
//         {
//             for( ; i <= size.width - 16; i += 16 )
//             {
//                 int t0 = ((int*)(src0 + i))[0];
//                 int t1 = ((int*)(src1 + i))[0];

//                 ((int*)(dst0 + i))[0] = t1;
//                 ((int*)(dst1 + i))[0] = t0;

//                 t0 = ((int*)(src0 + i))[1];
//                 t1 = ((int*)(src1 + i))[1];

//                 ((int*)(dst0 + i))[1] = t1;
//                 ((int*)(dst1 + i))[1] = t0;

//                 t0 = ((int*)(src0 + i))[2];
//                 t1 = ((int*)(src1 + i))[2];

//                 ((int*)(dst0 + i))[2] = t1;
//                 ((int*)(dst1 + i))[2] = t0;

//                 t0 = ((int*)(src0 + i))[3];
//                 t1 = ((int*)(src1 + i))[3];

//                 ((int*)(dst0 + i))[3] = t1;
//                 ((int*)(dst1 + i))[3] = t0;
//             }

//             for( ; i <= size.width - 4; i += 4 )
//             {
//                 int t0 = ((int*)(src0 + i))[0];
//                 int t1 = ((int*)(src1 + i))[0];

//                 ((int*)(dst0 + i))[0] = t1;
//                 ((int*)(dst1 + i))[0] = t0;
//             }
//         }

//         for( ; i < size.width; i++ )
//         {
//             uchar t0 = src0[i];
//             uchar t1 = src1[i];

//             dst0[i] = t1;
//             dst1[i] = t0;
//         }
//     }
// }

void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();

  int size = rows * cols;

  char* new_array_ptr = static_cast<char*>(malloc(channels * size * sizeof(char)));

  if(flip_type==Horizontal){
    register char *nlp1, *nrp1;
    register char *lp1, *rp1;
    for(int k=0; k<channels; k++){
      for(int l=0, r=cols-1; l<r; l++, r--){
        
        int page_size = k * size;
        int index_1 = page_size + l * rows;
        int index_5 = page_size + r * rows;

        nlp1 = &new_array_ptr[index_1];
        nrp1 = &new_array_ptr[index_5];

        lp1 = &array_ptr[index_1];
        rp1 = &array_ptr[index_5];
        for(int i=0; i<rows; i+=32){
          *((double*)nlp1) = *((double*)rp1);
          *((double*)nrp1) = *((double*)lp1);

          *((double*)nlp1+1) = *((double*)rp1+1);
          *((double*)nrp1+1) = *((double*)lp1+1);

          *((double*)nlp1+2) = *((double*)rp1+2);
          *((double*)nrp1+2) = *((double*)lp1+2);

          *((double*)nlp1+3) = *((double*)rp1+3);
          *((double*)nrp1+3) = *((double*)lp1+3);
        
          nlp1+=32;
          nrp1+=32;
          lp1+=32;
          rp1+=32;
        }
      }
    }
  }else if(flip_type==Vertical){
    register char *ntp1, *nbp1;
    register char *tp1, *bp1;

    for(int k=0; k<channels; k++){
      for(int i=0; i<cols-1; i++){

        int page_size = k * size;
        int index_t = page_size + i * rows;
        int index_b = page_size + i * rows + (rows-1);

        ntp1 = &new_array_ptr[index_t];
        nbp1 = &new_array_ptr[index_b];

        tp1 = &array_ptr[index_t];
        bp1 = &array_ptr[index_b];

        for(int t=0, b=rows-1; t<b; t+=4, b-=4){
          *(ntp1) = *(bp1);
          *(nbp1) = *(tp1);

          *(ntp1+1) = *(bp1-1);
          *(nbp1-1) = *(tp1+1);

          *(ntp1+2) = *(bp1-2);
          *(nbp1-2) = *(tp1+2);

          *(ntp1+3) = *(bp1-3);
          *(nbp1-3) = *(tp1+3);

          ntp1+=4;
          nbp1-=4;
          tp1+=4;
          bp1-=4;
        }
      }
    }
  }
  out_ptr->Reset(channels, rows, cols, new_array_ptr);
}

void Crop(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();

  if(x<0 || y<0){
    return;
  }

  char* new_array_ptr = static_cast<char*>(malloc(channels * width * height * sizeof(char)));

  int min_h = std::min(x+height, rows);
  int min_w = std::min(y+width, cols);


  register char *np, *p;

  for(int k=0; k<channels; k++){
    int size = k * rows * cols;
    int nsize = k * width * height;

    for(int j=y; j<min_w; j++){
        np = new_array_ptr + nsize + (j-y) * height;
        p = array_ptr + size + j * rows + x;
      for(int i=x; i<min_h; i+=32){
        // new_array_ptr[k * width * height + (j-y) * height + (i-x)] = array_ptr[k * rows * cols + j * rows + i];
          *((double*)np) = *((double*)p);
          *((double*)np+1) = *((double*)p+1);
          *((double*)np+2) = *((double*)p+2);
          *((double*)np+3) = *((double*)p+3);

          np+=32;
          p+=32;
      }
    }
  }

  out_ptr->Reset(channels, height, width, new_array_ptr);
}


void Pad(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int top_pad, int bottom_pad, int left_pad, int right_pad){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();

  int new_rows = top_pad + bottom_pad + rows;
  int new_cols = left_pad + right_pad + cols;

  char* new_array_ptr = static_cast<char*>(malloc(channels * new_rows * new_cols * sizeof(char)));

  for(int k=0; k<channels; k++){
    int size = k * rows * cols;
    int nsize = k * new_rows * new_cols;

    register char *np, *p;

    for(int j=0; j<cols; j++){
      p = array_ptr + size + j * rows;
      np = new_array_ptr + nsize + (j+left_pad) * new_rows + top_pad;
      for(int i=0; i<rows; i+=32){
        // new_array_ptr[k * new_rows * new_cols + (j+left_pad) * new_rows + (i+top_pad)] = array_ptr[k * rows * cols + j * rows + i];
        *((double*)np) = *((double*)p);
        *((double*)np+1) = *((double*)p+1);
        *((double*)np+2) = *((double*)p+2);
        *((double*)np+3) = *((double*)p+3);

        np+=32;
        p+=32;
      }
    }
  }

  out_ptr->Reset(channels, new_rows, new_cols, new_array_ptr);
}

void Erase(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width, char value){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();

  if(x<0 || y<0){
    return;
  }

  char* new_array_ptr = static_cast<char*>(malloc(channels * rows * cols * sizeof(char)));
  memcpy(new_array_ptr, array_ptr, channels * rows * cols * sizeof(char));

  int min_h = std::min(x+height, rows);
  int min_w = std::min(y+width, cols);

  for(int k=0; k<channels; k++){
    for(int j=y; j<min_w; j++){
      for(int i=x; i<min_h; i++){
        new_array_ptr[k * rows * cols + j * rows + i] = value;
      }
    }
  }

  out_ptr->Reset(channels, rows, cols, new_array_ptr);
}

void ConvertBGRToGray(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr){
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();  

  char* new_array_ptr = static_cast<char*>(malloc(rows * cols * sizeof(char)));
  memset(new_array_ptr, static_cast<int64_t>(0), rows * cols * sizeof(char));


  register char *np, *p1, *p2, *p3;
  np = new_array_ptr;
  p1 = array_ptr;
  p2 = array_ptr + rows * cols;
  p3 = array_ptr + 2 * rows * cols;

  // float r[] = {0.0f, 0.0f, 0.0f, 0.0f};
  // float g[] = {0.0f, 0.0f, 0.0f, 0.0f};
  // float b[] = {0.0f, 0.0f, 0.0f, 0.0f};

  // float k1[] = {0.114f, 0.114f, 0.114f, 0.114f};
  // float k2[] = {0.587f, 0.587f, 0.587f, 0.587f};
  // float k3[] = {0.2989f, 0.2989f, 0.2989f, 0.2989f};

  // __m128 mk1 = _mm_load_ps(&k1[0]);
  // __m128 mk2 = _mm_load_ps(&k2[0]);
  // __m128 mk3 = _mm_load_ps(&k3[0]);

  // __m128 mr;
  // __m128 mg;
  // __m128 mb;
  // __m128 res;
  // for(int j=0; j<cols; j++){
  //   for(int i=0; i<rows; i+=4){
  //     r[0] = (float) *p1;
  //     r[1] = (float) *(p1+1);
  //     r[2] = (float) *(p1+2);
  //     r[3] = (float) *(p1+3);

  //     g[0] = (float) *p2;
  //     g[1] = (float) *(p2+1);
  //     g[2] = (float) *(p2+2);
  //     g[3] = (float) *(p2+3);

  //     b[0] = (float) *p3;
  //     b[1] = (float) *(p3+1);
  //     b[2] = (float) *(p3+2);
  //     b[3] = (float) *(p3+3);

  //     mr = _mm_load_ps(&r[0]);
  //     mg = _mm_load_ps(&g[0]);
  //     mb = _mm_load_ps(&b[0]);

  //     mr = _mm_mul_ps(mk1, mr);
  //     mg = _mm_mul_ps(mk2, mg);
  //     mb = _mm_mul_ps(mk3, mb);

  //     res = _mm_add_ps(mr, mg);
  //     res = _mm_add_ps(mb, res);

  //     *np = (char) res[0];
  //     *(np+1) = (char) res[1];
  //     *(np+2) = (char) res[2];
  //     *(np+3) = (char) res[3];

  //     np+=4;
  //     p1+=4;
  //     p2+=4;
  //     p3+=4;
  //   }
  // }


  for(int j=0; j<cols; j++){
    for(int i=0; i<rows; i+=4){
      *np = 0.114 * *p1 + 0.587 * *p2 + 0.587 * *p3;
      *(np+1) = 0.114 * *(p1+1) + 0.587 * *(p2+1) + 0.587 * *(p3+1);
      *(np+2) = 0.114 * *(p1+2) + 0.587 * *(p2+2) + 0.587 * *(p3+2);
      *(np+3) = 0.114 * *(p1+3) + 0.587 * *(p2+3) + 0.587 * *(p3+3);
    }
  }
  out_ptr->Reset(1, rows, cols, new_array_ptr);
}
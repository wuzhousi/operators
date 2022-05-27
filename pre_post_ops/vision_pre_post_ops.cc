#include "vision_pre_post_ops.h"

// void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type){
//   int channels = ptr->get_channels();
//   int cols = ptr->get_cols();
//   int rows = ptr->get_rows();
//   char* array_ptr = ptr->get_array_ptr();

//   int size = rows * cols;

//   char* new_array_ptr = static_cast<char*>(malloc(channels * size * sizeof(char)));
//   char* head_new_array_ptr = new_array_ptr;

//   int* tab = static_cast<int*>(malloc(channels * size * sizeof(int)));; 

//   for(int i = 0; i < cols; i++ )
//     for( int k = 0; k < rows; k++ )
//         tab[i * rows + k] = (cols - i - 1) * rows + k;

//   int j = 0;
//   int limit = cols / 2 * rows;
//   if(flip_type==Horizontal){
//     for(int k=0; k<channels; k++){
//       for(int i=0; i<limit; i++){
//           j = tab[i];
//           char t0 = array_ptr[i], t1 =array_ptr[j];
//           new_array_ptr[i] = t1; new_array_ptr[j] = t0;
//       }
//       if(k<channels-1){
//         array_ptr=array_ptr+size, new_array_ptr=new_array_ptr+size;
//       }
//     }
//   }else if(flip_type==Vertical){
//     for(int k=0; k<channels; k++){
//       for(int i=0; i<cols-1; i++){
//         for(int t=0, b=rows-1; t<b; t++, b--){
//           new_array_ptr[k * cols * rows + i * rows + t] = array_ptr[k * cols * rows + i * rows + b];
//           new_array_ptr[k * cols * rows + i * rows + b] = array_ptr[k * cols * rows + i * rows + t];
//         }
//       }
//     }
//   }

//   out_ptr->Reset(channels, rows, cols, head_new_array_ptr);
// }


void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  char* array_ptr = ptr->get_array_ptr();

  int size = rows * cols;

  char* new_array_ptr = static_cast<char*>(malloc(channels * size * sizeof(char)));
  
  register char *nlp1, *nrp1;
  register char *lp1, *rp1;

  if(flip_type==Horizontal){
    for(int k=0; k<channels; k++){
      for(int l=0, r=cols-1; l<r; l++, r--){
        
        int page_size = k * size;
        int index_1 = page_size + l * rows;
        int index_5 = page_size + r * rows;

        nlp1 = &new_array_ptr[index_1];
        nrp1 = &new_array_ptr[index_5];

        lp1 = &array_ptr[index_1];
        rp1 = &array_ptr[index_5];

        for(int i=0; i<rows; i=i+4){
          *nlp1 = *rp1;
          *nrp1 = *lp1;

          *(nlp1+1) = *(rp1+1);
          *(nrp1+1) = *(lp1+1);


          *(nlp1+2) = *(rp1+2);
          *(nrp1+2) = *(lp1+2);


          *(nlp1+3) = *(rp1+3);
          *(nrp1+3) = *(lp1+3);

          nlp1+=4;
          nrp1+=4;
          lp1+=4;
          rp1+=4;
        }
      }
    }
  }else if(flip_type==Vertical){
    for(int k=0; k<channels; k++){
      for(int i=0; i<cols-1; i++){
        for(int t=0, b=rows-1; t<b; t++, b--){
          new_array_ptr[k * cols * rows + i * rows + t] = array_ptr[k * cols * rows + i * rows + b];
          new_array_ptr[k * cols * rows + i * rows + b] = array_ptr[k * cols * rows + i * rows + t];
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

  for(int k=0; k<channels; k++){
    for(int j=y; j<min_w; j++){
      for(int i=x; i<min_h; i++){
        new_array_ptr[k * width * height + (j-y) * height + (i-x)] = array_ptr[k * rows * cols + j * rows + i];
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
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        new_array_ptr[k * new_rows * new_cols + (j+left_pad) * new_rows + (i+top_pad)] = array_ptr[k * rows * cols + j * rows + i];
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

  for(int j=0; j<cols; j++){
    for(int i=0; i<rows; i++){
      new_array_ptr[j * rows + i] = 0.114 * array_ptr[0 * rows * cols + j * rows + i];
    }
  }

  for(int j=0; j<cols; j++){
    for(int i=0; i<rows; i++){
      new_array_ptr[j * rows + i] = 0.587 * array_ptr[1 * rows * cols + j * rows + i];
    }
  }

  for(int j=0; j<cols; j++){
    for(int i=0; i<rows; i++){
      new_array_ptr[j * rows + i] = 0.2989 * array_ptr[2 * rows * cols + j * rows + i];
    }
  }

  out_ptr->Reset(1, rows, cols, new_array_ptr);
}
#include "vision_pre_post_ops.h"

void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  double* array_ptr = ptr->get_array_ptr();

  double* new_array_ptr = static_cast<double*>(malloc(channels * rows * cols * sizeof(double)));

  
  if(flip_type==Horizontal){
    for(int k=0; k<channels; k++){
      for(int l=0, r=cols-1; l<r; l++, r--){
        for(int i=0; i<rows-1; i++){
          new_array_ptr[k * cols * rows + l * rows + i] = array_ptr[k * cols * rows + r * rows + i];
          new_array_ptr[k * cols * rows + r * rows + i] = array_ptr[k * cols * rows + l * rows + i];
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
  double* array_ptr = ptr->get_array_ptr();

  if(x<0 || y<0){
    return;
  }

  double* new_array_ptr = static_cast<double*>(malloc(channels * width * height * sizeof(double)));

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
  double* array_ptr = ptr->get_array_ptr();

  int new_rows = top_pad + bottom_pad + rows;
  int new_cols = left_pad + right_pad + cols;

  double* new_array_ptr = static_cast<double*>(malloc(channels * new_rows * new_cols * sizeof(double)));

  for(int k=0; k<channels; k++){
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        new_array_ptr[k * new_rows * new_cols + (j+left_pad) * new_rows + (i+top_pad)] = array_ptr[k * rows * cols + j * rows + i];
      }
    }
  }

  out_ptr->Reset(channels, new_rows, new_cols, new_array_ptr);
}

void Erase(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width, double value){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  double* array_ptr = ptr->get_array_ptr();

  if(x<0 || y<0){
    return;
  }

  double* new_array_ptr = static_cast<double*>(malloc(channels * rows * cols * sizeof(double)));
  memcpy(new_array_ptr, array_ptr, channels * rows * cols * sizeof(double));

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
  double* array_ptr = ptr->get_array_ptr();  

  double* new_array_ptr = static_cast<double*>(malloc(rows * cols * sizeof(double)));
  memset(new_array_ptr, static_cast<int64_t>(0), rows * cols * sizeof(double));

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
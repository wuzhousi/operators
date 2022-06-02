#include"my_array.h"

void MyArray::Reset(int channels, int rows, int cols, unsigned char* array_ptr){
  this->channels = channels;
  this->rows = rows;
  this->cols = cols;
  if(this->array_ptr){
    free(this->array_ptr);
  }
  this->array_ptr = array_ptr;
}

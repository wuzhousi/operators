#ifndef OPERATORS_PRE_POST_OPS_MY_ARRAY
#define OPERATORS_PRE_POST_OPS_MY_ARRAY

#include<iostream>

class MyArray{
 public:
  explicit MyArray(): channels(0), rows(0), cols(0), array_ptr(nullptr){}
  explicit MyArray(int channels, int rows, int cols, char* array_ptr): channels(channels), rows(rows), cols(cols), array_ptr(array_ptr){}
  ~MyArray(){
    if(array_ptr){
      free(array_ptr);
    }
  }
  int get_channels();
  int get_rows();
  int get_cols();
  char* get_array_ptr();
  void Reset(int channels, int rows, int cols, char* array_ptr);
  MyArray(const MyArray&) = delete;
  MyArray& operator=(const MyArray&) = delete;

 private:
  int channels, rows, cols;
  char* array_ptr;
};

inline int MyArray::get_channels(){
  return channels;
}

inline int MyArray::get_rows(){
  return rows;
}

inline int MyArray::get_cols(){
  return cols;
}

inline char* MyArray::get_array_ptr(){
  return array_ptr;
}

#endif
